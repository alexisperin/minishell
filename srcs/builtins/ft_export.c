/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/21 16:07:47 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_export(t_cmds *cmd, char **env)
{
	char	**new_env;

	new_env = 0;
	if (!cmd->str[1])
	{
		printf("Print env sorted");
		return (1);
	}
	else
	{
		*env = ft_strjoin(*env, cmd->str[1]);
	}
	return (1);
}
