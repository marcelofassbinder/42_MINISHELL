/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:24:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/27 20:48:18 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*open_here_doc(t_redir *redir, t_shell *shell)
{
	char	*buffer;

	buffer = ft_calloc(sizeof(char), 1);
	if (!buffer)
		shell_error(shell, "Calloc Error: here_doc", 0, true);
	dup2(STDERR_FILENO, STDIN_FILENO);
	return (write_here_doc(buffer, redir, shell));
}

char	*write_here_doc(char *buffer, t_redir *redir, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(STDERR_FILENO, "minishell: warning: ");
			ft_printf(STDERR_FILENO, "here-document delimited by end-of-file");
			ft_printf(STDERR_FILENO, "wanted `%s')\n", redir->file);
			break ;
		}
		line = add_backslash_n(line, shell);
		if (!ft_strncmp(line, redir->file, ft_strlen(redir->file))
			&& ft_strlen(line) == ft_strlen(redir->file) + 1)
		{
			free(line);
			break ;
		}
		if (redir->file_status == GENERAL)
			line = expand_here_doc(line, shell);
		buffer = ft_strjoin(buffer, line);
		free(line);
	}
	return (buffer);
}

char	*add_backslash_n(char *line, t_shell *shell)
{
	char	*new_line;
	int		len;

	len = ft_strlen(line);
	new_line = ft_calloc(sizeof(char), ft_strlen(line) + 2);
	if (!new_line)
		shell_error(shell, "Calloc Error: here_doc expansion", 0, true);
	ft_memcpy(new_line, line, len);
	new_line[len] = '\n';
	free(line);
	return (new_line);
}

int	run_here_doc(t_redir *redir, t_shell *shell)
{
	char	*buffer;
	int		fd[2];

	sig_heredoc();
	buffer = open_here_doc(redir, shell);
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
	shell->array_fd_here_doc[redir->id] = fd[0];
	return (1);
}

void	open_all_heredocs(void *root, t_shell *shell)
{
	enum e_type	node_type;
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
	else if (node_type == REDIR_IN || node_type == REDIR_OUT
		|| node_type == D_REDIR_OUT || node_type == HERE_DOC)
	{
		redir = (t_redir *)root;
		if (node_type == HERE_DOC)
			run_here_doc(redir, shell);
		open_all_heredocs(redir->down, shell);
	}
	else if (node_type == WORD)
		return ;
}
