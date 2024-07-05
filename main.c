/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:53 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/05 17:23:48 by vivaccar         ###   ########.fr       */
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

char	**copy_envs(t_shell *shell, char **envp)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (envp[i])
		i++;
	env_copy = ft_calloc(sizeof(char *), i + 1);
	if (!env_copy)
		shell_error(shell, "Caloc error: env\n");
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env_copy);
}

t_shell	*init_shell(int ac, char **av, char **envp)
{
	t_shell	*shell;
	(void)av;

	if (ac != 1)
		exit (127);
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		shell_error(shell, "Shell Caloc Error\n");
	shell->envp = copy_envs(shell, envp);
	shell->exit_status = 0;
	shell->pid = 0;
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
	if (g_status == 130 || g_status == 131)
		shell->exit_status = g_status;
	return (shell);
}

bool	is_pipe_root(void *root)
{
	enum e_type	node_type;

	if (!root)
		return (false);
	node_type = *(enum e_type *)root;
	if (node_type == PIPELINE)
		return (true);
	return (false);
}

void	start_minishell(t_shell *shell)
{
	tokenizer(shell->token_list, shell->line, shell);
	shell->root = parse(shell->token_list->first);
	if (!is_pipe_root(shell->root))
		run_in_parent(shell->root, shell);
	if (shell->exit_status == 127 || is_pipe_root(shell->root))
	{
 		if (fork() == 0)
		{
			start_child_signals();
			run(shell->root, shell);
			safe_exit(shell, shell->exit_status);
		}
		g_status = -1;
		wait(&shell->exit_status);
		g_status = 0;
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	}
	free_tree(shell->root);
	free(shell->line);
	free_token_list(shell->token_list);
	free(shell->token_list);
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
			free(shell->token_list);
			free(shell->line);
			continue ;
		}
		start_minishell(shell);
	}
}
