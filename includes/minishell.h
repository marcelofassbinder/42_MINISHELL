/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/27 21:02:27 by vivaccar         ###   ########.fr       */
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
# include <limits.h>

//	CHAR DEFINES
# define PIPE '|'
# define DOLLAR '$'
# define R_IN '<'
# define R_OUT '>'
# define S_QTE 39
# define D_QTE 34

//	PROCESS DEFINES
# define PARENT 1
# define CHILD 2

//	COLORS DEFINES
# define RED "\033[1;3;31m"
# define GREEN "\033[1;3;32m"
# define YELLOW "\033[1;3;93m"
# define RESET "\033[0m"

//	EXIT CODES
# define EXIT_SYNTAX 2
# define EXIT_CMD 127

// GLOBAL VARIABLES
extern int	g_received_signal;

//	STATUS
enum e_status
{
	GENERAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

//	TOKEN TYPES
enum e_type
{
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
	T_FILE,
	T_NULL
};

//	TOKEN STRUCTS
typedef struct s_token
{
	enum e_status	status;
	enum e_type		type;
	struct s_token	*prev;
	struct s_token	*next;
	char			*data;
}					t_token;

typedef struct s_token_list
{
	t_token		*first;
	t_token		*last;
}				t_token_list;

//	PARSING STRUCTS
typedef struct s_exec
{
	enum e_type		type;
	bool			is_builtin;
	char			**cmd_args;
}					t_exec;

typedef struct s_redir
{
	enum e_type		type;
	enum e_status	file_status;
	void			*down;
	int				id;
	char			*file;
}					t_redir;

typedef struct s_pipe
{
	enum e_type		type;
	void			*left;
	void			*right;
}					t_pipe;

//	MAIN STRUCT
typedef struct s_shell
{
	t_token_list	*token_list;
	void			*root;
	int				*array_fd_here_doc;
	int				exit_status;
	int				pid;
	int				process;
	int				fd_in;
	int				fd_out;
	int				count_hd;
	char			**envp;
	char			*line;
	char			*path;
}					t_shell;

//	SHELL STRUCT
t_shell			*init_shell(int ac, char **av, char **envp);
bool			is_pipe_root(void *root);
int				ft_get_pid(t_shell *shell);
char			**copy_envs(t_shell *shell, char **envp);

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
bool			special_char(char *str);

//	TOKENS.C
enum e_status	append_quotes(t_token_list *token_list,
					char c, enum e_status status);
enum e_status	change_status(t_token_list *token_list,
					char c, enum e_status status, enum e_type type);
void			tokenizer(t_token_list *token_list, char *line, t_shell *shell);
void			print_token_list(t_token_list *token_list);
void			tokenizer(t_token_list *token_list, char *line, t_shell *shell);
void			find_files(t_token_list *token_list);
void			prepare_tokens(t_token_list *token_list, t_shell *shell);
void			token_redir_pipe(t_token_list *token_list);
void			repeated_quotes(t_token_list *token_list);
void			prepare_tokens(t_token_list *token_list, t_shell *shell);
void			repeated_quotes(t_token_list *token_list);
bool			is_redir(t_token *token);
int				is_type_word(char c);

//APPEND.C
void			append_token(t_token_list *token_list,
					char *str, enum e_status status, enum e_type type);
void			append_token(t_token_list *token_list, char *str,
					enum e_status status, enum e_type type);
int				append_word(t_token_list *token_list, char *line,
					enum e_status status, int i);
int				append_redir(t_token_list *token_list, char *line,
					enum e_status status, int i);

//SIGNALS.C
void			start_sig(void);
void			signal_handler(int signal);
void			sig_default(void);
void			sig_ignore(void);
void			sig_heredoc(void);
void			sig_default(void);
bool			check_syntax(char *line);
int				get_status(int status);

//FREE tokens
void			free_token_list(t_token_list *token_list);
void			delete_node(t_token_list *token_list, t_token *tmp);

//FREE
void			free_tree(void *root);
void			free_envs(char **envp);
void			free_and_exit(t_shell *shell);
void			shell_error(t_shell *shell, char *str,
					int error, bool exit_flag);
void			error_message(int error, char *str);
void			free_all_allocated_memory(t_shell *shell, int free_shell);
int				return_parent_error(t_shell *shell, char *str, int error);

//EXPAND.C & EXPAND_UTILS.C && EXPAND_CASES.C
void			handle_expansion(t_token_list *token_list,
					t_token **tmp, t_shell *shell);
void			check_dollar(t_token_list *token_list,
					t_shell *shell, t_token *tmp);
bool			is_special(int c);
bool			not_expand_heredoc_eof(t_token **tmp);
int				count_special(char *data, char special);
char			*expand(char *data, t_shell *shell);
char			*expand_mode(char *data, t_shell *shell);
char			*expand_digit(char *data);
char			*expand_minishell(char *data);
char			*expand_special(char *data);
char			*expand_mode(char *data, t_shell *shell);
char			*expand_normal(char *data, t_shell *shell);
char			*expand_digit(char *data);
char			*expand_minishell(char *data);
char			*expand_special(char *data);
char			find_special(char *data);
char			*expand_aux(char *data, char *to_expand,
					char *rest, t_shell *shell);
char			**copy_envs(t_shell *shell, char **envp);
t_token			*get_eof_status(t_token *tmp);

//GETVALUES.C
bool			is_special(int c);
char			*get_var_value(char *env);
char			*expand_aux(char *data, char *to_expand,
					char *rest, t_shell *shell);
char			**copy_envs(t_shell *shell, char **envp);

//GETVALUES.C
void			insert_token(char *data, t_token **token);
void			split_env(t_token_list *token_list, t_token **token);
void			insert_token(char *data, t_token **token);
void			split_env(t_token_list *token_list, t_token **token);
int				ft_get_pid(t_shell *shell);
char			*get_var_value(char *env);
char			*ft_get_env(char *data, t_shell *shell);

//JOIN.C
t_token			*join_nodes(t_token_list *token_list, t_token *token);
void			join_spaces(t_token_list *token_list);
void			join_quotes(t_token_list *token_list);
void			join_words(t_token_list *token_list);

//PARSE.C
t_token			*get_next_redir(t_token *token);
t_token			*find_last_or_pipe(t_token *token, int flag);
t_token			*get_previous_redir(t_token *token);
t_token			*get_next_token(t_token *token);
t_redir			*create_new_redir(void *down, t_token *token,
					t_shell *shell, int flag);
t_redir			*define_redir(void *down, t_token *token, t_shell *shell);
t_pipe			*build_pipe(void *left, void *right);
void			*parse(t_token *token, t_shell *shell);
void			*build_exec(t_token *token, t_shell *shell);
void			*build_redir(void *down, t_token *token, t_shell *shell);
void			define_redir_file(t_redir *redir, t_token *token);
bool			is_local_variable(t_token *token);
bool			last_redir(t_token *token);
bool			is_builtin(char *str);
bool			has_word(t_token *token);
int				count_args(t_token *token);
char			**define_cmd_args(t_token *token);

//RUN
void			run_execve(t_exec *exec, t_shell *shell);
void			run_exec(t_exec *exec, t_shell *shell);
void			run_redir(t_redir *redir, t_shell *shell);
void			run_pipe(t_pipe *pipe_str, t_shell *shell);
void			run_builtin(t_exec *exec, t_shell *shell);
void			run_in_parent(void *root, t_shell *shell);
void			run(void *root, t_shell *shell);
void			handle_exec_error(int execve_ret, t_exec *exec, t_shell *shell);
void			manage_pipe_exit(int *fd, int *pid, t_shell *shell);
bool			has_no_file(t_shell *shell, t_redir *redir, int exit_flag);
int				redirect_in(t_shell *shell, t_redir *redir, int exit_flag);
int				redirect_out(t_shell *shell, t_redir *redir, int exit_flag);
int				check_exit_sig(int *exit_code);
int				redirect(t_shell *shell, t_redir *redir, int exit_flag);
int				has_pipe(t_shell *shell);
int				return_parent_error(t_shell *shell, char *str, int error);
char			**get_path(char *path_from_env);

//BUILTINS
void			echo(char **cmd_args, t_shell *shell);
void			pwd(t_shell *shell);
void			unset(char **cmd_args, t_shell *shell);
void			cd(char **cmd_args, t_shell *shell);
void			cd_home(char **cmd_args, t_shell *shell);
void			update_old_pwd(char *update_old, t_shell *shell);
void			exit_cmd(char **cmd_args, t_shell *shell);
void			exit_number(char **cmd_args, t_shell *shell);
void			exit_line(t_shell *shell);
bool			env_exist(char *var_name, char **env);
int				check_option_n(char **cmd_args);
int				str_is_digit(char *str);
int				check_option_n(char **cmd_args);
int				str_is_digit(char *str);
int				cd_old_dir(char *old_pwd_env, char *update_old, t_shell *shell);
char			*get_variable_name(char *environment);
char			*remove_plus(char *environment);
char			**replace_env(char *environment, t_shell *shell, int mode);
char			**set_new_env(char *environment, t_shell *shell, int mode);

//EXPORT
void			export(char **cmd_args, t_shell *shell);
void			swap(char **envs, int j);
void			print_env_x(t_shell *shell);
bool			env_exist(char *var_name, char **env);
int				add_mode(char *environmenent);
char			**export_error(t_shell *shell, char *var_name,
					char *environment);
char			*remove_plus(char *environment);
char			*get_variable_name(char *environment);
char			*do_replace(char *environment, char *envp, int mode);
char			**replace_env(char *environment, t_shell *shell, int mode);
char			**set_new_env(char *environment, t_shell *shell, int mode);
char			**add_envp(char *environment, t_shell *shell);
char			**ordered_envs(t_shell *shell, int size);

//SAFE_FUNCTIONS.C
void			safe_chdir(char *chdir_arg, t_shell *shell, int flag);
int				safe_fork(t_shell *shell);
char			*safe_getcwd(char *buf, size_t size, t_shell *shell);

//teste
int				ft_get_pid(t_shell *shell);
int				count_here_doc(t_shell *shell);

//	HEREDOC
void			open_all_heredocs(void *root, t_shell *shell);
int				run_here_doc(t_redir *redir, t_shell *shell);
int				*create_here_doc_array(t_shell *shell);
char			*open_here_doc(t_redir *redir, t_shell *shell);
char			*write_here_doc(char *buffer, t_redir *redir, t_shell *shell);
char			*expand_here_doc(char *line, t_shell *shell);
char			*replace_expanded_var(char *line,
					char *after_doll, t_shell *shell);
char			*copy_before_doll(char *line, char *after_doll, t_shell *shell);
char			*copy_after_doll(char *new_line, char *line, char *after_doll);
char			*add_backslash_n(char *line, t_shell *shell);

#endif