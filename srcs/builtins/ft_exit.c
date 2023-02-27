/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:32:45 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/27 16:08:03 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_exit(t_cmds *cmd, int type)
{
	unsigned char	ret;
	int	check;

	ret = 0;
	check = 0;
	if (type)
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
	else
		ft_putstr_fd("exit\n", 1);
	if (cmd->str[1] && cmd->str[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (cmd->str[1])
	{
		ret = ft_atoi_check(cmd->str[1], &check);
		if (check)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->str[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
	exit(ret);
}
