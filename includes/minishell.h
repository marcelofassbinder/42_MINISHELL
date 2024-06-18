/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/18 18:50:54 by mfassbin         ###   ########.fr       */
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

#define PIPE '|'
#define ENV '$'
#define REDIR_IN '<'
#define REDIR_OUT '>'

#define S_QUOTE 39
#define D_QUOTE 34

enum t_status{
	general = 0,
	in_s_quote,
	in_d_quote
};

enum t_type{
	w_space = 3,
	word,
	pipeline,
	env,
	redir_in,
	redir_out,
	d_redir_out,
	here_doc
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
t_token_list	*append_char_token(t_token_list *token_list, char c, int status, int type);
t_token_list	*append_str_token(t_token_list *token_list, char *str, int status, int type);
void 	print_token_list(t_token_list *token_list);


//SIGNALS.C
void	start_sigaction(void);

#endif