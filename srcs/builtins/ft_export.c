/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/23 16:36:46 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_export(t_cmds *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmd->str[1])
	{
		printf("Print env sorted");
		return (1);
	}
	else
	{
		while (shell->env[i])
		{
			if (shell->env[i + 1] == NULL)
			{
				
			}
		}
	}
	return (1);
}
