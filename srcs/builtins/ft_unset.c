/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:45:56 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/26 11:34:36 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**unset_arr(char **env, char **rtn, char *str)
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
			if (!rtn[j])
			{
				ft_free_arr(rtn);
				return (rtn);
			}
			j++;
		}
		i++;
	}
	return (rtn);
}

int	ft_unset(t_cmds *cmd, t_shell *shell)
{
	char	**temp;
	char	**rtn;
	int		i;
	
	i = 0;
	while (shell->env[i])
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	temp = unset_arr(shell->env, rtn, cmd->str[1]);
	ft_free_arr(shell->env);
	shell->env = temp;
	return (1);
}