/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/29 19:25:44 by vivaccar         ###   ########.fr       */
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

void	echo(char **cmd_args)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		ft_printf(1, "%s", cmd_args[i]);
		i++;
		if (cmd_args[i])
			ft_printf(1, " ");
	}	
	ft_printf(1, "\n");
}

void	run_exec(t_exec *exec)
{
	if (!ft_strncmp(exec->cmd_args[0], "echo", ft_strlen(exec->cmd_args[0])))
		echo(exec->cmd_args);
}
void	run_redir(t_redir *redir)
{
	int	fd;
	
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	run((void *)redir->down);
	close(fd);
}

void	run(void *root)
{
	enum e_type	node_type;
	t_exec		*exec;
	t_redir		*redir;
	t_pipe		*pipe;

	node_type = *(enum e_type *)root;
	//printf("\nType\n = %i", node_type);
	if (node_type == WORD)
	{
		exec = (t_exec *)root;
		run_exec(exec);
		//printf("%s", exec->cmd_args[0]);
	}
	else if (node_type == REDIR_IN || node_type == D_REDIR_OUT || node_type == REDIR_OUT)
	{
		redir = (t_redir *)root;
		run_redir(redir);
		//printf("%s", redir->file);
	}
	else if (node_type == PIPELINE)
	{
		pipe = (t_pipe *)root;
		//printf("%i", pipe->type);
	}
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_token_list token_list;
	void		*root;
	int			status;

	root = NULL;
	(void) av;	
	(void) ac;
	(void) env;
	start_sigaction();
	while (1)
	{
		token_list = (t_token_list){0};
		line = readline(GREEN"GAU"RED"SHE"YELLOW"LL--> "RESET);
		add_history(line);
		if (!line)
			exit_line(line);
		if (!check_syntax(line))
		{
			free(line);
			continue ;
		}
		tokenizer(&token_list, line);
		//test_redir(&token_list);
		root = parse(token_list.first);
		if (fork() == 0)
		{
			run(root);
			exit(status);
		}
		wait(&status);
		//printf("\n\n\n\n");
		//print_tree(root, "", true);
		free(line);
		free_token_list(&token_list);
	}
}
