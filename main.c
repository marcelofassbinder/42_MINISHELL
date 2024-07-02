/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:53 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/02 17:29:02 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void printExec(t_exec *exec, const char *prefix, bool isLeft) {
    printf("%s%sEXEC: ", prefix, isLeft ? "├── " : "└── ");
    for (int i = 0; exec->cmd_args[i] != NULL; i++) {
        printf("%s ", exec->cmd_args[i]);
    }
    printf("(builtin: %s)\n", exec->is_builtin ? "true" : "false");
}

void printRedir(t_redir *redir, const char *prefix, bool isLeft) {
    printf("%s%sREDIR: %s\n", prefix, isLeft ? "├── " : "└── ", redir->file);
    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "│   " : "    ");
    print_tree(redir->down, newPrefix, false); // 'false' ensures the proper prefix for the next level
}

void printPipe(t_pipe *pipe, const char *prefix, bool isLeft) {
    printf("%s%sPIPE:\n", prefix, isLeft ? "├── " : "└── ");
    char newPrefixLeft[256];
    char newPrefixRight[256];
    snprintf(newPrefixLeft, sizeof(newPrefixLeft), "%s│   ", prefix);
    snprintf(newPrefixRight, sizeof(newPrefixRight), "%s    ", prefix);
    print_tree(pipe->left, newPrefixLeft, true);
    print_tree(pipe->right, newPrefixRight, false);
}

void print_tree(void *node, const char *prefix, bool isLeft) {
    if (node == NULL) return;

    enum e_type type = *(enum e_type *)node;
    
    if (type == WORD)
		printExec((t_exec *)node, prefix, isLeft);
	else if (type == D_REDIR_OUT || type == REDIR_IN || type == REDIR_OUT)
		printRedir((t_redir *)node, prefix, isLeft);
	else if(type == PIPELINE)
		printPipe((t_pipe *)node, prefix, isLeft);
}

void	shell_error(t_shell *shell, char *str)
{
	if (shell->token_list)
	{
		if (shell->token_list->first)
			free_token_list(shell->token_list);
		free(shell->token_list);
	}
	if (shell->root)
		free_tree(shell->root);
	if (shell->line)
		free(shell->line);
	if (shell)
		free(shell);
	ft_printf(2, "%s", str);
	exit(2);
}

t_shell	*init_shell(int ac, char **av, char **envp)
{
	t_shell	*shell;
	(void)ac;
	(void)av;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		shell_error(shell, "Shell Caloc Error\n");
	shell->envp = envp;
	shell->exit_status = 0;
	return (shell);
}

int	g_status;

t_shell	*ft_read_line(t_shell *shell)
{
	g_status = 0;
	shell->line = readline(GREEN"GAU"RED"SHE"YELLOW"LL--> "RESET);
	add_history(shell->line);
	if (!shell->line)
		exit_line(shell);
	shell->token_list = ft_calloc(sizeof(t_token_list), 1);
	if (!shell->token_list)
		shell_error(shell, "Token list Aloc Error\n");
	shell->token_list->first = NULL;
	shell->token_list->last = NULL;
	if (g_status == 130)
		shell->exit_status = 130;
	return (shell);
}

/* Function to handle the received signal, during the execution of 
	this function other received signals are blocked if it is in the mask. */
void	signal_handler(int signal, siginfo_t *info, void *content)
{
	(void)info;
	(void)content;

	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

/* Initialize the signal handling structure (sigaction), define the
masks (signals that are blocked if the signal handler is handling a signal).*/
void	start_sigaction(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;

	sigemptyset(&sa_quit.sa_mask);
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_flags = 0;
	sa_int.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sa_int.sa_sigaction = &signal_handler;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaddset(&sa_quit.sa_mask, SIGINT);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigaction(SIGINT, &sa_int, NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_shell		*shell;

	shell = init_shell(ac, av, envp);
	start_sigaction();
	while (1)
	{
		shell = ft_read_line(shell);
		if (!check_syntax(shell->line) || !shell->line[0])
		{
			free(shell->line);
			continue ;
		}
		tokenizer(shell->token_list, shell->line, shell);
		shell->root = parse(shell->token_list->first);
		if (fork() == 0)
		{
			run(shell->root, shell);
			safe_exit(shell, shell->exit_status);
		}
		wait(&shell->exit_status);
		shell->exit_status = WEXITSTATUS(shell->exit_status);
		free_tree(shell->root);
		free(shell->line);
		free_token_list(shell->token_list);
		free(shell->token_list);
	}
}
