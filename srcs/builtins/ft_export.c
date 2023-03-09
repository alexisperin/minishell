/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/09 15:22:23 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	if_exist(char **env, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	if (!env)
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len))
		{
			free(env[i]);
			env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_arr(t_shell *shell, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], str, len - 2))
			ft_strjoin(shell->env[i], str);
		i++;
	}
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

	i = 0;
	while (shell->env[i])
			i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	new_arr(shell->env, rtn, str);
	ft_free_arr(shell->env);
	shell->env = rtn;
	return (1);
}

int	ft_export(t_cmds *cmd, t_shell *shell, char *str)
{
	int		i;

	i = 1;
	if (!str && !cmd->str[1])
	{
		sort_env(shell);
		print_env(shell->sorted_env);
		return (1);
	}
	if (str)
	{
		if (!if_exist(shell->env, str))
			send_arr(shell, str);
	}
	else
	{
		while (cmd->str[i])
		{
			check_and_send(shell, cmd->str[i]);
			i++;
		}
	}
	return (1);
}
