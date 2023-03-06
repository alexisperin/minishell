/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:19:53 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/06 16:23:51 by aburnott         ###   ########.fr       */
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
		// if (cmd->str[0][i] == ' ')
		// 	break ;
		// if (cmd->str[0][i] == '=')
		// 	check = 1;
		if(!check_validity(&cmd->str[0][i]))
			break ;
		i++;
	}
	if (check)
	{
		ft_export(0, shell, cmd->str[0]);
		return (1);
	}
	return (0);
}