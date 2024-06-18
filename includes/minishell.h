/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:32:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/18 13:03:26 by mfassbin         ###   ########.fr       */
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

enum t_status{
	GENERAL = 0,
	IN_S_QUOTE,
	IN_D_QUOTE
};

enum t_type{
	W_SPACE = 0,
	WORD = 1,
	PIPE = '|',
	ENV = '$',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	D_REDIR_OUT = 2,
	HERE_DOC = 3,
};

typedef struct s_token{
	enum t_status status;
	enum t_type type;
	char *data;
}

void	start_sigaction(void);

#endif