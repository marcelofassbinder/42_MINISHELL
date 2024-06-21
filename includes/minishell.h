/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/21 15:19:17 by vivaccar         ###   ########.fr       */
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
# include <stdio.h>
# include <stdbool.h>

enum e_status {
	GENERAL,
	IN_S_QUOTE,
	IN_D_QUOTE,
};

enum e_type {
	W_SPACE = 0,
	WORD = 1,
	PIPE = '|',
	ENV = '$',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	D_REDIR_OUT = 2,
	HERE_DOC = 3,
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

void	start_sigaction(void);
bool	check_syntax(char *line);

#endif