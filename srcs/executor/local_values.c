/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:19:53 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/05 16:37:56 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	check_equ(t_cmds *cmd, t_shell *shell)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (cmd->str[0][i])
	{
		if (cmd->str[0][i] == ' ')
			break ;
		if (cmd->str[0][i] == '=')
			check = 1;
		i++;
	}
	if (check)
	{
		ft_export(0, shell, cmd->str[0]);
		return (1);
	}
	return (0);
}