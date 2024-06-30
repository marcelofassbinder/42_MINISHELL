/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/30 19:33:32 by vinivaccari      ###   ########.fr       */
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

char **get_path(char *path_from_env)
{
	char **path;
	int	i;

	if (!path_from_env)
		return (NULL);
	path = ft_split(path_from_env,':');
	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;		
	}
	return(path);
}

void	run_execve(t_exec *exec, char **envp)
{	
	char **path;
	char *path_cmd;
	int i;
	
	path = get_path(getenv("PATH"));
	i = 0;
	if (access(exec->cmd_args[0], F_OK) == 0)
		execve(exec->cmd_args[0], exec->cmd_args, envp);
	while(path[i])
	{
		path_cmd = ft_strjoin(path[i], exec->cmd_args[0]);
		if (access(path_cmd, F_OK) == 0)
			execve(path_cmd, exec->cmd_args, envp);
		free(path_cmd);
		i++;
	}
	ft_printf(2, "%s: command not found\n", exec->cmd_args[0]);
}

void	run_exec(t_exec *exec, char **envp)
{
	//if (exec->is_builtin)
	if (!exec->is_builtin)
		run_execve(exec, envp);		
	if (!ft_strncmp(exec->cmd_args[0], "echo", ft_strlen(exec->cmd_args[0])))
		echo(exec->cmd_args);
	exit(0);
}
void	run_redir(t_redir *redir, char **envp)
{
	int	fd;

	// Verificar se o arquivo ja existe e nao alterar as permissoes caso exista.
	if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_printf(2, "%s: No such file or directory\n", redir->file);
			return ;
		}
		dup2(fd, STDOUT_FILENO);
	}
	else if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			ft_printf(2, "%s: No such file or directory\n", redir->file);
			return ;
		}
		dup2(fd, STDIN_FILENO);
	}
	else if (redir->type == D_REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			ft_printf(2, "%s: No such file or directory\n", redir->file);
			return ;
		}	
		dup2(fd, STDOUT_FILENO);
	}
	run((void *)redir->down, envp);
	close(fd);
}

void	run_pipe(t_pipe *pipe_str, char **envp)
{
	int	fd[2];
	int pid;
	
	if (pipe(fd) == -1)
		ft_printf(2, "Pipe Error\n");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run(pipe_str->left, envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		run(pipe_str->right, envp);
	}
	wait(NULL);
	wait(NULL);
}

void	run(void *root, char **envp)
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
		run_exec(exec, envp);
		//printf("%s", exec->cmd_args[0]);
	}
	else if (node_type == REDIR_IN || node_type == D_REDIR_OUT || node_type == REDIR_OUT)
	{
		redir = (t_redir *)root;
		run_redir(redir, envp);
		//printf("%s", redir->file);
	}
	else if (node_type == PIPELINE)
	{
		pipe = (t_pipe *)root;
		run_pipe(pipe, envp);
		//printf("%i", pipe->type);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_token_list token_list;
	void		*root;
	int			status;

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
			exit(status);
		}
		wait(&status);
		//printf("\n\n\n\n");
		free(line);
		free_token_list(&token_list);
	}
}
