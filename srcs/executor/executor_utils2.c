/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:15:42 by aperin            #+#    #+#             */
/*   Updated: 2023/03/07 17:20:31 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_execve(t_cmds *cmd, t_shell *shell, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, cmd->str[0]);
		if (access(tmp, F_OK) == 0
			&& execve(tmp, cmd->str, shell->env) == -1)
		{
			ft_free_arr(path);
			perror(cmd->str[0]);
			exit(-1);
		}
		free(tmp);
		i++;
	}
	ft_free_arr(path);
	ft_putstr_fd(cmd->str[0], STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
	exit(127);
}
