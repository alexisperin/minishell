/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:32:45 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/15 00:01:53 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_exit(t_cmds *cmd)
{
	//Need to handle return value
	int	ret;
	int	check;

	ret = 0;
	check = 0;
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
			ft_putstr_fd(": numeric argument required", 2);
		}
		else if (ret > 255)
			ret = 255;
	}
	if (ret < 0)
		ret = 255 + ret + 1;
	printf("\n\n\nEXIT VAL: %d", ret); //TO REMOVE
	return (ret);
}
