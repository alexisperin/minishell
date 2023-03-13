/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:27:37 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/13 10:41:11 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	last_check(int i, t_cmds *cmd)
{
	int	j;

	while ((ft_strncmp(cmd->str[i], "-n", 2) == 0))
	{
		j = 1;
		while (cmd->str[i][j] == 'n')
			j++;
		if (cmd->str[i][j] != 0)
			break ;
		else
			i++;
	}
	return (i);
}

static int	check_n(t_cmds *cmd, int i, int *check, int *n)
{
	if ((ft_strncmp(cmd->str[i], "-n", 2) == 0) && i == 1)
	{
		while (cmd->str[i][*check] && cmd->str[i][*check] == 'n')
			*check += 1;
		if (cmd->str[i][*check] == 0)
		{
			*check = 0;
			*n = 0;
			i++;
		}
		else
			i = 1;
		if (i > 0)
			i = last_check(i, cmd);
	}
	return (i);
}

int	ft_echo(t_cmds *cmd)
{
	int	i;
	int	n;
	int	check;

	i = 1;
	n = 1;
	check = 1;
	i = check_n(cmd, i, &check, &n);
	while (cmd->str[i])
	{
		ft_putstr_fd(cmd->str[i], 1);
		if (cmd->str[i + 1] != 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n && check)
		ft_putchar_fd('\n', 1);
	return (0);
}
