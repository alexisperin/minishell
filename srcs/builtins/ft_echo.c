/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:27:37 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/22 16:23:01 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_echo(t_cmds *cmd)
{
	int	i;
	int	n;
	int	check;

	i = 1;
	n = 1;
	check = 1;
	while (cmd->str[i])
	{
		if ((ft_strncmp(cmd->str[i], "-n", 2) == 0) && i == 1)
		{
			while (cmd->str[++i][check] && cmd->str[++i][check] == 'n')
				check++;
			if (cmd->str[i][check] == 0)
			{
				check = 0;
				n = 0;
			}
			else
				i = 0;
			if (i > 1)
				while ((ft_strncmp(cmd->str[i], "-n", 2) == 0))
					i++;
		}
		ft_putstr_fd(cmd->str[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (n && check)
		ft_putchar_fd('\n', 1);
	return (1);
}
