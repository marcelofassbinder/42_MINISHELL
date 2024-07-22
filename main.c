/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:53 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 18:20:30 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	shell_error(t_shell *shell, char *str, int error, bool exit_flag)
{
	int status;

	status = shell->exit_status;
	if (error == 1) // erro de comando
		ft_printf(STDERR_FILENO, "%s: command not found\n", str);
	else if (error == 2) // erro de arquivo ou diretorio
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
	else if (error == 3) // erro de permissao
		ft_printf(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
	else if (error == 4) // redirect para nao expandivel
		ft_printf(STDERR_FILENO, "minishell: ambiguous redirect\n", str);
	else
		ft_printf(STDERR_FILENO, "%s\n", str);
	if (shell->envp)
		free_envs(shell->envp);
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
	if (shell->old_pwd)
		free(shell->old_pwd);
	if (shell->fd_heredoc)
		free(shell->fd_heredoc);
	if (shell)
		free(shell);
	if (exit_flag)
		exit(status);	
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
	shell->old_pwd = safe_getcwd(NULL, 0, shell);
	shell->pid = ft_get_pid(shell);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	//shell->path = getenv("PATH");
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

int has_here_doc(t_shell *shell)
{
	t_token *token;
	int count;

	token = shell->token_list->first;
	count = 0;
	while(token)
	{
		if (token->type == HERE_DOC)
			count++;
		token = token->next;
	}
	return (count);
}
void	open_all_heredocs(void *root, t_shell *shell)
{
	enum e_type node_type;
	t_pipe		*pipe;
	t_redir		*redir;

	if (!root)
		return ;
	node_type = *(enum e_type *)root;
	if (node_type == PIPELINE)
	{
		pipe = (t_pipe *)root;
		open_all_heredocs(pipe->left, shell);
		open_all_heredocs(pipe->right, shell);
	}
	else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT || node_type == HERE_DOC)
	{
		redir = (t_redir *)root;
		if (node_type == HERE_DOC)
			run_here_doc(redir, shell);
		open_all_heredocs(redir->down, shell);
	}
	else if (node_type == WORD)
		return ;
}

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

void	start_minishell(t_shell *shell)
{	
	tokenizer(shell->token_list, shell->line, shell);
	shell->count_hd = has_here_doc(shell);
	add_here_doc_fd(shell, 0, 0, true);
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
	create_new_redir(NULL, NULL, NULL, 1);
	free_tree(shell->root);
	free(shell->line);
	free_token_list(shell->token_list);
	free(shell->token_list);
	free(shell->fd_heredoc);
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
			shell->exit_status = EXIT_SYNTAX;
			free(shell->token_list);
			free(shell->line);
			continue ;
		}
		start_minishell(shell);
	}
}