/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:24:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/22 15:42:50 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*write_here_doc(t_redir *redir, t_shell *shell)
{
	char *buffer;
	char *line;

	buffer = ft_calloc(sizeof(char), 1);
	if (!buffer)
		shell_error(shell, "Calloc Error: here_doc", 0, true);
	dup2(STDERR_FILENO, STDIN_FILENO);
	while(1)
	{
		line = readline(">");
		line = add_backslash_n(line, shell);
		if (redir->file_status == GENERAL)
			line = expand_here_doc(line, shell);
		if (!ft_strncmp(line, redir->file, ft_strlen(redir->file)) && ft_strlen(line) == ft_strlen(redir->file) + 1)
		{
			free(line);
			break ;
		}
		buffer = ft_strjoin(buffer, line);
		free(line);
	}
	return (buffer);
}

char	*add_backslash_n(char *line, t_shell *shell)
{
	char	*new_line;
	int 	len;

	len = ft_strlen(line);
	new_line = ft_calloc(sizeof(char), ft_strlen(line) + 2);
	if (!new_line)
		shell_error(shell, "Calloc Error: here_doc expansion", 0, true);
	ft_memcpy(new_line, line, len);
	new_line[len] = '\n';
	free(line);
	return(new_line);
}

int	run_here_doc(t_redir *redir, t_shell *shell)
{
	char *buffer;
	int fd[2];

	sig_heredoc();
	buffer = write_here_doc(redir, shell);
	if (pipe(fd) == -1)
		shell_error(shell, "Pipe error\n", 0, true);	
	if (safe_fork(shell) == 0)
	{
		close(fd[0]);
		write(fd[1], buffer, ft_strlen(buffer));
		free(buffer);
		dup2(fd[1], shell->fd_out);
		close(fd[1]);
		free_and_exit(shell);
	}
	wait(NULL);
	free(buffer);
	close(fd[1]);
	add_here_doc_fd(shell, fd[0], redir->id, false);
	return (1);
}

void	add_here_doc_fd(t_shell *shell, int fd_here_doc, int pos, bool init)
{
	if (init)
	{
		shell->fd_heredoc = ft_calloc(sizeof(int), shell->count_hd + 1);
		if (!shell->fd_heredoc)
			shell_error(shell, "Calloc error: heredoc", 0, true);
		shell->fd_heredoc[shell->count_hd] = -1;
		return ;
	}
	shell->fd_heredoc[pos] = fd_here_doc;
}