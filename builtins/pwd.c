/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:35:16 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/22 15:27:25 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_shell *shell)
{
	char	*pwd;

	pwd = safe_getcwd(NULL, 0, shell);
	ft_printf(1, "%s\n", pwd);
	free(pwd);
	shell->exit_status = EXIT_SUCCESS;
}
