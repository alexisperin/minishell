/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:32:45 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/08 14:47:37 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	checker(char *str, unsigned char *ret)
{
	int	check;

	check = 0;
	*ret = ft_atoi_check(str, &check);
	if (check == 2)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
	}
	else if (check == 1)
		exit(*ret);
}

int	ft_exit(t_cmds *cmd, int type)
{
	unsigned char	ret;

	ret = 0;
	if (type)
	{
		ft_putstr_fd("exit\n", STDOUT);
		exit (0);
	}
	else if (cmd->pid)
		ft_putstr_fd("exit\n", STDOUT);
	if (cmd->str[1] && cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (1);
	}
	if (cmd->str[1])
		checker(cmd->str[1], &ret);
	return (0);
	//exit(&ret);
}
