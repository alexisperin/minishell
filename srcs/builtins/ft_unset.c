/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:45:56 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/13 11:51:07 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	unset_arr(char **env, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) != 0)
		{
			rtn[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
}

int	ft_unset(t_cmds *cmd, t_shell *shell)
{
	char	**rtn;
	int		i;
	int		j;

	j = 1;
	while (cmd->str[j])
	{
		i = 0;
		while (shell->env[i])
			i++;
		rtn = ft_calloc(i, sizeof(char *));
		unset_arr(shell->env, rtn, cmd->str[j]);
		ft_free_arr(shell->env);
		shell->env = rtn;
		j++;
	}
	return (0);
}
