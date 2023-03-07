/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:34:25 by aperin            #+#    #+#             */
/*   Updated: 2023/03/07 18:54:40 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	is_builtin(t_cmds *cmd)
{
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		return (true);
	return (false);
}

int	ft_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		perror("dup");
		exit(-1);
	}
	return (new_fd);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		exit(-1);
	}
	close(fd1);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(-1);
	}
	return (pid);
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(-1);
	}
}
