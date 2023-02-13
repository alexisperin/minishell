/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:27:37 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/13 14:45:51 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_putstr_dollar(char *str, char **env)
{
	int	i;
	int	count;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			count = i++;
			while (str[count] != ' ' && str[count])
				count++;
		}
	}
}

int	ft_echo(t_cmds *cmd, char **env)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while (cmd->str[i])
	{
		if (ft_strncmp(cmd->str[i], "-n", 2) == 0 && i == 1)
		{
			n = 0;
			i++;
		}
		ft_putstr_dollar(cmd->str[i], env);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (n)
		ft_putchar_fd('\n', 1);
	return (1);
}
