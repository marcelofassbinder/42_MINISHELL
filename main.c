/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:38:50 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/25 12:43:04 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_token_list token_list;

	(void) av;
	(void) ac;
	(void) env;
	start_sigaction();
	while (1)
	{
		token_list = (t_token_list){0};
		line = readline("minishell --> ");
		if (!line)
			exit_line(line);
		if (!check_syntax(line))
			continue ;
		tokenizer(&token_list, line);
		add_history(line);
		
		free(line);
		free_token_list(&token_list);
	}
}
