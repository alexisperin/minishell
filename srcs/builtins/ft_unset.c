/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:45:56 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/07 13:16:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	unset_arr(char **env, char **rtn, char *str)
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
	
	i = 0;
	while (shell->env[i])
		i++;
	rtn = ft_calloc(i + 1, sizeof(char *));
	unset_arr(shell->env, rtn, cmd->str[1]);
	ft_free_arr(shell->env);
	shell->env = rtn;
	return (1);
}