/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/01 14:57:50 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	check_validity(char *str)
{
	int i;
	int	equ;

	i = 0;
	equ = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equ = 1;
		i++;
	}
	return (equ);
}

char	**new_arr(char **env, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(env[i]);
		}
		else
			rtn[i] = ft_strdup(env[i]);
		i++;
	}
	if (!rtn[i])
	{
		ft_free_arr(rtn);
		return (rtn);
	}
	return (rtn);
}

int	send_arr(t_shell *shell, char *str)
{
	int		i;
	char	**rtn;
	char	**temp;
	
	i = 0;
	while (shell->env[i])
			i++;
		rtn = ft_calloc(sizeof(char *), i + 2);
			temp = new_arr(shell->env, rtn, str);
		ft_free_arr(shell->env);
		shell->env = temp;
	return (1);
}

int	ft_export(t_cmds *cmd, t_shell *shell, char *str)
{
	int		i;

	i = 0;
	if (!str && !cmd->str[1])
	{
		printf("Print env sorted");
		return (1);
	}
	else if (!str && ft_strncmp(cmd->str[1], "=", 1) == 0)
	{
		ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
	}
	else if (!str && !check_validity(cmd->str[1]))
		return (1);
	else
	{
		if (str)
			send_arr(shell, str);
		else
		{
			while (cmd->str[i])
			{
				send_arr(shell, cmd->str[i]);
				i++;
			}
		}
	}
	return (1);
}
