/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:29:40 by aperin            #+#    #+#             */
/*   Updated: 2023/03/06 16:19:26 by aperin           ###   ########.fr       */
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

int	execute_builtin(t_cmds *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		shell->return_value = ft_pwd();
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		shell->return_value = ft_echo(cmd);
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0)
		shell->return_value = ft_cd(cmd, shell);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		shell->return_value = ft_export(cmd, shell, 0);
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		shell->return_value = ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		shell->return_value = ft_env(shell->env);
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		shell->return_value = ft_exit(cmd, 0);
	else
		return (0);
	return (1);
}

void	execute_cmd(t_cmds *cmd, t_shell *shell)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
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
			if (access(tmp, F_OK) == 0
				&& execve(tmp, cmd->str, shell->env) == -1)
			{
				perror(cmd->str[0]);
				exit(1); //TO UPDATE ???
			}
			free(tmp);
			i++;
		}
		ft_free_arr(path);
		ft_putstr_fd(cmd->str[0], STDERR);
		ft_putstr_fd(": command not found\n", STDERR);
		exit(127);
	}
	exit(0);
}

bool	single_cmd(t_shell *shell)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = ft_dup(STDIN);
	save_stdout = ft_dup(STDOUT);
	if (is_builtin(shell->cmds))
	{
		shell->cmds->pid = 1;
		handle_redirections(shell->cmds, shell);
		execute_builtin(shell->cmds, shell);
		ft_dup2(save_stdin, STDIN);
		ft_dup2(save_stdout, STDOUT);
		return (true);
	}
	else if (check_equ(shell->cmds, shell))
		return (true);
	return (false);
}

void	execute(t_shell *shell)
{
	t_cmds	*curr;
	int		prev_fd;
	int		status;

	prev_fd = -1;
	curr = shell->cmds;
	if (curr->next == NULL && single_cmd(shell))
		return ;
	while (curr)
	{
		if (curr->next != NULL)
			ft_pipe(curr->pipefd);
		curr->pid = ft_fork();
		if (curr->pid == 0)
		{
			if (curr->n > 1)
			{
				ft_dup2(prev_fd, STDIN);
				close(prev_fd);
			}
			if (curr->next != NULL)
			{
				ft_dup2(curr->pipefd[1], STDOUT);
				close(curr->pipefd[1]);
				close(curr->pipefd[0]);
			}
			if (handle_redirections(curr, shell))
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
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			shell->return_value = WEXITSTATUS(status);
		curr = curr->next;
	}
}
