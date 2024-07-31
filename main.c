/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:53 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/31 16:57:29 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_received_signal;

t_shell	*ft_read_line(t_shell *shell)
{
	start_sig();
	start_sig();
	shell->process = CHILD;
	shell->line = NULL;
	shell->line = readline("GAUSHELL--> ");
	if (!shell->line)
		exit_line(shell);
	shell->token_list = ft_calloc(sizeof(t_token_list), 1);
	if (!shell->token_list)
		shell_error(shell, "Calloc Error: tokens\n", 0, true);
	shell->token_list->first = NULL;
	shell->token_list->last = NULL;
	if (g_received_signal == SIGINT)
		shell->exit_status = 130;
	return (shell);
}

void	prepare_new_prompt(t_shell *shell)
{
	create_new_redir(NULL, NULL, NULL, 1);
	free_tree(shell->root);
	free(shell->line);
	free_token_list(shell->token_list);
	free(shell->token_list);
	free(shell->array_fd_here_doc);
	create_new_redir(NULL, NULL, NULL, 1);
	shell->root = NULL;
	shell->line = NULL;
	shell->token_list = NULL;
	shell->array_fd_here_doc = NULL;
}

void	minishell(t_shell *shell)
{
	add_history(shell->line);
	tokenizer(shell->token_list, shell->line, shell);
	shell->count_hd = count_here_doc(shell);
	shell->array_fd_here_doc = create_here_doc_array(shell);
	shell->root = parse(shell->token_list->first, shell);
	if (!is_pipe_root(shell->root) && !shell->count_hd)
		run_in_parent(shell->root, shell);
	if (shell->process == CHILD || shell->count_hd)
	{
		if (safe_fork(shell) == 0)
		{
			shell->process = CHILD;
			sig_default();
			if (shell->count_hd)
				open_all_heredocs(shell->root, shell);
			run(shell->root, shell);
			free_and_exit(shell);
		}
		sig_ignore();
		wait(&shell->exit_status);
		shell->exit_status = get_status(shell->exit_status);
	}
	prepare_new_prompt(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell		*shell;
	bool		syntax;

	shell = init_shell(ac, av, envp);
	while (1)
	{
		shell = ft_read_line(shell);
		syntax = check_syntax(shell->line);
		if (!syntax || !shell->line[0])
		{
			if (!syntax)
			{
				add_history(shell->line);
				shell->exit_status = EXIT_SYNTAX;
			}
			free(shell->token_list);
			free(shell->line);
			continue ;
		}
		minishell(shell);
	}
}
