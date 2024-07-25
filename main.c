/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:53 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/25 21:53:50 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_status(int status)
{
	if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_printf(1, "\n");
			return (130);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf(1, "Quit (core dumped)\n");
			return (131);
		}
	}
	return (0);
}

char	**copy_envs(t_shell *shell, char **envp)
{
	int		i;
	char	**env_copy;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	env_copy = ft_calloc(sizeof(char *), i + 1);
	if (!env_copy)
		shell_error(shell, "Calloc Error: envp copy\n", 0, true);
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

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		shell_error(shell, "Calloc Error: shell struct\n", 0, true);
	if (ac != 1)
	{
		shell->exit_status = EXIT_CMD;
		shell_error(shell, av[1], 2, true);
	}
	shell->envp = copy_envs(shell, envp);
	shell->exit_status = 0;
	shell->pid = ft_get_pid(shell);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	return (shell);
}

int	g_received_signal;

t_shell	*ft_read_line(t_shell *shell)
{
	start_sig();
	shell->process = CHILD;
	shell->line = NULL;
	shell->line = readline(GREEN"GAU"RED"SHE"YELLOW"LL--> "RESET);
	add_history(shell->line);
	if (!shell->line)
		exit_cmd(NULL, shell);
	shell->token_list = ft_calloc(sizeof(t_token_list), 1);
	if (!shell->token_list)
		shell_error(shell, "Calloc Error: tokens\n", 0, true);
	shell->token_list->first = NULL;
	shell->token_list->last = NULL;
	if (g_received_signal == SIGINT)
		shell->exit_status = 130;
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

void	prepare_new_prompt(t_shell *shell)
{
	create_new_redir(NULL, NULL, NULL, 1);
	free_tree(shell->root);
	free(shell->line);
	free_token_list(shell->token_list);
	free(shell->token_list);
	free(shell->fd_heredoc);
	shell->root = NULL;
	shell->line = NULL;
	shell->token_list = NULL;
	shell->fd_heredoc = NULL;
}

void	start_minishell(t_shell *shell)
{	
	tokenizer(shell->token_list, shell->line, shell);
	shell->count_hd = count_here_doc(shell);
	save_here_doc_fd(shell, 0, 0, true);
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

	shell = init_shell(ac, av, envp);
	while (1)
	{
		shell = ft_read_line(shell);
		if (!check_syntax(shell->line) || !shell->line[0])
		{
			if (!shell->line[0])
				shell->exit_status = EXIT_SUCCESS;
			else
				shell->exit_status = EXIT_SYNTAX;
			free(shell->token_list);
			free(shell->line);
			continue ;
		}
		start_minishell(shell);
	}
}
