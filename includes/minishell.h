/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/21 15:39:48 by vivaccar         ###   ########.fr       */
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

#define PIPE '|'
#define DOLLAR '$'
#define REDIRECT_IN '<'
#define REDIRECT_OUT '>'

#define S_QUOTE 39
#define D_QUOTE 34

enum t_status {
	GENERAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

enum t_type{
	W_SPACE = 3,
	WORD,
	PIPELINE,
	ENV,
	REDIR_IN,
	REDIR_OUT,
	D_REDIR_OUT,
	HERE_DOC
};

typedef struct		s_token{
	enum t_status	status;
	enum t_type		type;
	struct s_token	*prev;
	struct s_token	*next;
	char 			*data;
}					t_token;

typedef struct	s_token_list{
	t_token 	*first;
	t_token 	*last;
}				t_token_list;


// TOKENS.C
void			tokenizer(char *line);
t_token_list *append_char_token(t_token_list *token_list, char c, enum t_status status, enum t_type type);
t_token_list	*append_str_token(t_token_list *token_list, char *str, enum t_status status, enum t_type type);
void 	print_token_list(t_token_list *token_list);
int is_type_word(char c, enum t_status status);
enum t_status change_status(char c, enum t_status status);


//SIGNALS.C
void	start_sigaction(void);
bool	check_syntax(char *line);

#endif