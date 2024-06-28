/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/28 17:45:44 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void printExec(t_exec *exec, int level) {
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("EXEC: ");
    for (int i = 0; exec->cmd_args[i] != NULL; i++) {
        printf("%s ", exec->cmd_args[i]);
    }
    printf("(builtin: %s)\n", exec->is_builtin ? "true" : "false");
}

void printRedir(t_redir *redir, int level) {
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("REDIR: %s\n", redir->file);
    print_tree(redir->down, level + 1);
}

void printPipe(t_pipe *pipe, int level) {
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("PIPE:\n");
    print_tree(pipe->left, level + 1);
    print_tree(pipe->right, level + 1);
}

void print_tree(void *node, int level)
{
    if (node == NULL) return;

    enum e_type	type = *(enum e_type *)node;
	
	if (type == WORD)
        printExec((t_exec *)node, level);
	if (type == REDIR_IN || type == REDIR_OUT || type == D_REDIR_OUT)
        printRedir((t_redir *)node, level);
    if (type == PIPELINE)
        printPipe((t_pipe *)node, level);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_token_list token_list;
	void		*root;

	root = NULL;
	(void) av;	
	(void) ac;
	(void) env;
	start_sigaction();
	while (1)
	{
		token_list = (t_token_list){0};
		line = readline(GREEN"GAU"RED"SHE"YELLOW"LL-->"RESET);
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
		printf("\n\n\n\n");
		print_tree(root, 0);
		free(line);
		free_token_list(&token_list);
	}
}
