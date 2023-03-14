/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:32:45 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/14 09:19:10 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	checker(char *str)
{
	int	check;

	check = 0;
	g_return_value = ft_atoi_check(str, &check);
	if (check == 1)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		g_return_value = 2;
	}
	else
		exit(g_return_value);
}

int	ft_exit(t_cmds *cmd, int type)
{
	if (type)
	{
		ft_putstr_fd("exit\n", STDOUT);
		exit(g_return_value);
	}
	else if (cmd->pid)
		ft_putstr_fd("exit\n", STDOUT);
	if (cmd->str[1] && cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (1);
	}
	if (cmd->str[1])
		checker(cmd->str[1]);
	exit(g_return_value);
}
