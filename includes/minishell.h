/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/25 18:47:30 by mfassbin         ###   ########.fr       */
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

# define PIPE '|'
# define DOLLAR '$'
# define R_IN '<'
# define R_OUT '>'

# define S_QTE 39
# define D_QTE 34


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
	D_QUOTE
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

//	PARSING STRUCTS
typedef struct		s_exec{
	enum e_type		type;
	char			**cmd_args;
	bool			is_builtin;
}					t_exec;

typedef struct		s_redir{
	enum e_type		type;
	char			*file;
	t_exec			*exec;
}					t_redir;

typedef struct		s_pipe{
	enum e_type		type;
	void			*left;
	void			*right;
}					t_pipe;


//	TOKENS.C
void			tokenizer(t_token_list *token_list, char *line);
void			print_token_list(t_token_list *token_list);
int				is_type_word(char c);
enum e_status	append_quotes(t_token_list *token_list, char c, enum e_status status);
enum e_status	change_status(t_token_list *token_list, char c, enum e_status status, enum e_type type);

//APPEND.C
void			append_token(t_token_list *token_list, char *str, enum e_status status, enum e_type type);
int				append_word(t_token_list *token_list, char *line, enum e_status status, int i);
int				append_redir(t_token_list *token_list, char *line, enum e_status status, int i);

//SIGNALS.C
void			start_sigaction(void);
bool			check_syntax(char *line);

//FREE.C
void			free_token_list(t_token_list *token_list);
void			free_env(t_token *token);
void			exit_line(char *line);
void			free_strings(char *s1, char *s2, char *s3);
void			delete_node(t_token_list *token_list, t_token *tmp);

//EXPAND.C
void			check_dollar(t_token_list *token_list);
char			*expand(char *data);
char			find_special(char *data);
int				count_special(char *data, char special);

//JOIN.C
void			join_spaces(t_token_list *token_list);
t_token			*join_nodes(t_token_list *token_list, t_token *token);
void			join_quotes(t_token_list *token_list);
void			join_words(t_token_list *token_list);

//PARSE.C
t_exec			*build_exec(t_token *token);
int				command_args(t_token *token);
void 			test_redir(t_token_list *token_list);


#endif