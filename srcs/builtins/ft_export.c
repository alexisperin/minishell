/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/25 13:48:18 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

int	ft_export(t_cmds *cmd, t_shell *shell, char *str)
{
	int		i;
	char	**temp;
	char	**rtn;
	int		cd;

	i = 0;
	cd = 0;
	if (str)
		cd = 1;
	if (!str && !cmd->str[1])
	{
		printf("Print env sorted");
		return (1);
	}
	else if (!str && ft_strncmp(cmd->str[1], "=", 1) == 0)
	{
		ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
	}
	else
	{
		while (shell->env[i])
			i++;
		rtn = ft_calloc(sizeof(char *), i + 2);
		if (cd)
			temp = new_arr(shell->env, rtn, str);
		else
			temp = new_arr(shell->env, rtn, cmd->str[1]);
		ft_free_arr(shell->env);
		shell->env = temp;
	}
	return (1);
}
