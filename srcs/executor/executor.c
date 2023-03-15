/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:29:40 by aperin            #+#    #+#             */
/*   Updated: 2023/03/15 10:20:30 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static bool	execute_currdir(t_cmds *cmd, t_shell *shell)
{
	if (cmd->str[0][0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", STDERR);
		exit(127);
	}
	if (ft_strchr(cmd->str[0], '/') == NULL)
		return (false);
	if (access(cmd->str[0], F_OK) == 0)
	{
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR);
			perror(cmd->str[0]);
			exit(126);
		}
	}
	return (false);
}

int	execute_builtin(t_cmds *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		g_return_value = ft_pwd();
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		g_return_value = ft_echo(cmd);
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0)
		g_return_value = ft_cd(cmd, shell);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		g_return_value = ft_export(cmd, shell, 0);
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		g_return_value = ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		g_return_value = ft_env(shell->env);
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		g_return_value = ft_exit(cmd);
	else
		return (0);
	return (1);
}

static void	execute_cmd(t_cmds *cmd, t_shell *shell)
{
	int		i;

	i = 0;
	if (!cmd->str[0])
		exit(0);
	if (!execute_builtin(cmd, shell) && !execute_currdir(cmd, shell))
	{
		while (shell->env && shell->env[i])
		{
			if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
				break ;
			i++;
		}
		if (shell->env[i])
			ft_execve(cmd, shell, ft_split(&shell->env[i][5], ':'));
		ft_execve(cmd, shell, NULL);
	}
	exit(g_return_value);
}

static void	handle_pipes(t_cmds *cmd, int prev_fd, t_shell *shell)
{
	sig_handler(1);
	if (cmd->next != NULL)
		ft_pipe(cmd->pipefd);
	cmd->pid = ft_fork();
	if (cmd->pid == 0)
	{
		sig_handler(2);
		if (cmd->n > 1)
			ft_dup2(prev_fd, STDIN);
		if (cmd->next != NULL)
		{
			ft_dup2(cmd->pipefd[1], STDOUT);
			close(cmd->pipefd[0]);
		}
		if (handle_redirections(cmd, shell))
			execute_cmd(cmd, shell);
		exit(g_return_value);
	}
}

void	execute(t_shell *shell)
{
	t_cmds	*curr;
	int		prev_fd;

	handle_heredocs(shell);
	prev_fd = -1;
	curr = shell->cmds;
	if (curr->next == NULL && single_cmd(shell))
		return ;
	while (curr && !shell->stop)
	{
		handle_pipes(curr, prev_fd, shell);
		close(prev_fd);
		prev_fd = curr->pipefd[0];
		close(curr->pipefd[1]);
		curr = curr->next;
	}
	ft_waitpid(shell);
}
