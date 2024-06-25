/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/25 15:38:38 by mfassbin         ###   ########.fr       */
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
		add_history(line);
		if (!line)
			exit_line(line);
		if (!check_syntax(line))
		{
			free(line);
			continue ;
		}
		tokenizer(&token_list, line);
		free(line);
		free_token_list(&token_list);
	}
}
