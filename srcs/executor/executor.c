/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:29:40 by aperin            #+#    #+#             */
/*   Updated: 2023/03/01 14:46:58 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	execute_currdir(t_cmds *cmd, t_shell *shell)
{
	if (ft_strchr(cmd->str[0], '/') == NULL)
		return (false);
	if (access(cmd->str[0], F_OK) == 0)
	{
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
			exit(0); // HANDLE ERROR
	}
	return (false);
}

bool	execute_builtin(t_cmds *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		return (ft_export(cmd, shell, 0));
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		return (ft_unset(cmd, shell));
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		return (ft_env(shell->env));
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		return (ft_exit(cmd, 0));
	return (0);
}

int	execute_cmd(t_cmds *cmd, t_shell *shell)
{
	int		i;
	int		ret;
	char	**path;
	char	*tmp;

	i = 0;
	ret = -1;
	if (!execute_builtin(cmd, shell) && !execute_currdir(cmd, shell))
	{
		while (shell->env[i])
		{
			if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
				break ;
			i++;
		}
		path = ft_split(&shell->env[i][5], ':');
		i = 0;
		while (path[i])
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = ft_strjoin_free(tmp, cmd->str[0]);
			if (access(tmp, F_OK) == 0)
				ret = execve(tmp, cmd->str, shell->env);
			free(tmp);
			i++;
		}
		ft_free_arr(path);
	}
	exit(0); // TO update
}

void	execute(t_shell *shell)
{
	t_cmds	*curr;
	int		prev_fd;

	prev_fd = -1;
	curr = shell->cmds;
	if (curr->next == NULL
		&& (check_equ(curr, shell) || execute_builtin(curr, shell)))
		return ;
	while (curr)
	{
		if (curr->next != NULL)
			pipe(curr->pipefd);
		curr->pid = fork();
		if (curr->pid == -1)
			exit(0); // HANDLE ERROR
		if (curr->pid == 0)
		{
			if (curr->n > 1)
			{
				dup2(prev_fd, STDIN); // HANDLE ERROR
				close(prev_fd);
			}
			if (curr->next != NULL)
			{
				dup2(curr->pipefd[1], STDOUT); //Protection
				close(curr->pipefd[1]);
				close(curr->pipefd[0]);
			}
			execute_cmd(curr, shell);
		}
		close(prev_fd);
		prev_fd = curr->pipefd[0];
		close(curr->pipefd[1]);
		curr = curr->next;
	}
	curr = shell->cmds;
	while (curr)
	{
		waitpid(curr->pid, NULL, 0);
		curr = curr->next;
	}
}
