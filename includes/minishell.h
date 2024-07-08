/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/08 14:05:29 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>

# define PIPE '|'
# define DOLLAR '$'
# define R_IN '<'
# define R_OUT '>'

# define S_QTE 39
# define D_QTE 34

# define PARENT 1
# define CHILD 2

//	COLORS
# define RESET "\033[0m"
# define RED "\033[1;3;31m"
# define GREEN "\033[1;3;32m"
# define YELLOW "\033[1;3;93m"

// GLOBAL VARIABLES
extern int g_status;

//	EXIT CODES
# define EXIT_CMD 127

//	STATUS
enum e_status{
	GENERAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

//	TOKEN TYPES
enum e_type{
	W_SPACE = 3,
	WORD,
	PIPELINE,
	ENV,
	REDIR_IN,
	REDIR_OUT,
	D_REDIR_OUT,
	HERE_DOC,
	S_QUOTE,
	D_QUOTE,
	T_FILE
};

//	TOKEN STRUCTS
typedef struct		s_token{
	enum e_status	status;
	enum e_type		type;
	struct s_token	*prev;
	struct s_token	*next;
	char			*data;
}					t_token;

typedef struct s_token_list{
	t_token		*first;
	t_token		*last;
}				t_token_list;


//	PARSING STRUCTS
typedef struct		s_exec{
	enum e_type		type;
	char			**cmd_args;
	bool			is_builtin;
}					t_exec;

typedef struct		s_redir{
	enum e_type		type;
	char			*file;
	void			*down;
}					t_redir;

typedef struct		s_pipe{
	enum e_type		type;
	void			*left;
	void			*right;
}					t_pipe;

//MAIN STRUCT
typedef struct		s_shell{
	t_token_list	*token_list;
	void			*root;
	char			**envp;
	char			*line;
	int				exit_status;
	int				pid;
	int				process;
}					t_shell;





//SYNTAX
bool			check_redir(char *str);
bool			check_pipe(char *str);
bool			redir_error(char *str);
bool			pipe_error(char *str);
bool			check_syntax(char *line);
bool			previous_is_redir(char *str);
bool			unclosed_quotes(char *str);
bool			empty_line(char *str);
bool			exceeded_token(char *str, int c);

//	TOKENS.C
void			tokenizer(t_token_list *token_list, char *line, t_shell *shell);
void			print_token_list(t_token_list *token_list);
int				is_type_word(char c);
enum e_status	append_quotes(t_token_list *token_list, char c, enum e_status status);
enum e_status	change_status(t_token_list *token_list, char c, enum e_status status, enum e_type type);
bool			is_redir(t_token *token);
void			find_files(t_token_list *token_list);

//APPEND.C
void			append_token(t_token_list *token_list, char *str, enum e_status status, enum e_type type);
int				append_word(t_token_list *token_list, char *line, enum e_status status, int i);
int				append_redir(t_token_list *token_list, char *line, enum e_status status, int i);

//SIGNALS.C
void			start_sigaction(void);
bool			check_syntax(char *line);
void			start_child_signals(void);

//FREE tokens
void			free_token_list(t_token_list *token_list);
void			exit_line(t_shell *shell);
void			free_strings(char *s1, char *s2, char *s3);
void			delete_node(t_token_list *token_list, t_token *tmp);

//FREE
void			free_tree(void *root);
void			free_envs(char **envp);
void			safe_exit(t_shell *shell);
void			shell_error(t_shell *shell, char *str, int error);

//EXPAND.C
void			check_dollar(t_token_list *token_list, t_shell *shell);
char			*expand(char *data, t_shell *shell);
char			find_special(char *data);
int				count_special(char *data, char special);

//JOIN.C
void			join_spaces(t_token_list *token_list);
t_token			*join_nodes(t_token_list *token_list, t_token *token);
void			join_quotes(t_token_list *token_list);
void			join_words(t_token_list *token_list);

//PARSE.C
void			*parse(t_token *token);
void			*build_exec(t_token *token);
void			*build_redir(void *down, t_token *token);
t_pipe			*build_pipe(void *left, void *right);
t_token			*get_next_redir(t_token *token);
bool			last_redir(t_token *token);
t_token			*find_last_or_pipe(t_token *token, int flag);
t_token			*get_previous_redir(t_token *token);
int				command_args(t_token *token);
bool			is_builtin(char *str);
t_redir 		*create_new_redir(void *down, t_token *token);
int				count_args(t_token *token);
char			**define_cmd_args(t_token *token);

//PRINT_TREE.C
void 	print_tree(void *node, const char *prefix, bool isLeft);
void printExec(t_exec *exec, const char *prefix, bool isLeft);
void printRedir(t_redir *redir, const char *prefix, bool isLeft);
void printPipe(t_pipe *pipe, const char *prefix, bool isLeft);


//RUN
void			run(void *root, t_shell *shell);
char 			**get_path(char *path_from_env);
void			run_execve(t_exec *exec, t_shell *shell);
void			run_exec(t_exec *exec, t_shell *shell);
void			run_redir(t_redir *redir, t_shell *shell);
void			run_pipe(t_pipe *pipe_str, t_shell *shell);
void			run_builtin(t_exec *exec, t_shell *shell);
void			run_in_parent(void *root, t_shell *shell);

//BUILTINS

void			echo(char **cmd_args, t_shell *shell);
void			env(char **cmd_args, t_shell *shell);
void			export(char **cmd_args, t_shell *shell);
void			pwd(t_shell *shell);
void			unset(char **cmd_args, t_shell *shell);
char			*get_variable_name(char *environment);
void			cd(char **cmd_args, t_shell *shell);

#endif