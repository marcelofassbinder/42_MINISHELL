/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/01 12:22:40 by vivaccar         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_token_list token_list;
	void		*root;

	root = NULL;
	(void) av;	
	(void) ac;
	start_sigaction();
	while (1)
	{
		token_list = (t_token_list){0};
		line = readline(GREEN"GAU"RED"SHE"YELLOW"LL--> "RESET);
		add_history(line);
		if (!line)
			exit_line(line);
		if (!check_syntax(line) || !line[0])
		{
			free(line);
			continue ;
		}
		tokenizer(&token_list, line);
		//test_redir(&token_list);
		root = parse(token_list.first);
		//print_tree(root, "", true);
		if (fork() == 0)
		{
			run(root, envp);
			free_tree(root);
			free_token_list(&token_list);
			exit(0);
		}
		wait(NULL);
		//printf("\n\n\n\n");
		free_tree(root);
		free(line);
		free_token_list(&token_list);
	}
}
