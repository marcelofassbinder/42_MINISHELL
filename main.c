/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:53 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/10 18:21:45 by vinivaccari      ###   ########.fr       */
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
	else
		ft_printf(STDERR_FILENO, "%s\n", str);
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
	shell->pid = 0;
	shell->old_pwd = safe_getcwd(NULL, 0, shell);
	return (shell);
}

int	g_status;

t_shell	*ft_read_line(t_shell *shell)
{
	g_status = 0;
	shell->process = CHILD;
	shell->line = readline(GREEN"GAU"RED"SHE"YELLOW"LL--> "RESET);
	add_history(shell->line);
	if (!shell->line)
		exit_line(shell);
	shell->token_list = ft_calloc(sizeof(t_token_list), 1);
	if (!shell->token_list)
		shell_error(shell, "Calloc Error: tokens\n", 0, true);
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
	if (shell->process == CHILD)
	{
 		if (safe_fork(shell) == 0)
		{
			shell->process = CHILD;
			start_child_signals();
			run(shell->root, shell);
			free_and_exit(shell);
		}
		wait(&shell->exit_status);
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
