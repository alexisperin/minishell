/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:29:40 by aperin            #+#    #+#             */
/*   Updated: 2023/02/24 21:36:42 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	execute_builtin(t_cmds *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		return (ft_export(cmd, shell));
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		return (ft_unset(cmd, shell));
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		return (ft_env(shell->env));
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		return (ft_exit(cmd));
	return (0);
}

int	execute_cmd(t_cmds *cmd, t_shell *shell)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	if (!execute_builtin(cmd, shell))
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
				execve(tmp, cmd->str, shell->env);
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
	pid_t	pid;

	curr = shell->cmds;
	while (curr)
	{
		if (!execute_builtin(curr, shell))
		{
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE); // HANDLE ERROR
			if (pid == 0)
				execute_cmd(curr, shell);
			waitpid(pid, NULL, 0); // Handle error
		}
		curr = curr->next;
	}
}

void	execute2(t_shell *shell)
{
	pid_t	pid[2];
	int		pipefd[2];

	// int fd = open("file", O_CREAT | O_RDWR);
	
	pipe(pipefd); // Protection
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT); //Protection
		// dup2(fd, STDIN);
		// close(pipefd[1]);
		execute_cmd(shell->cmds, shell);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		// dup2(fd, STDOUT);
		execute_cmd(shell->cmds->next, shell);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0); // Handle error
	waitpid(pid[1], NULL, 0); // Handle error
}

// void	execute_cmd(t_cmds *cmd, char **env, int fd_in, int fd_out)
// {
// 	cmd->pid = fork();
// 	if (cmd->pid == -1)
// 		exit(0); // Handle error
// 	if (cmd->pid != 0)
// 		return ;
// 	if (cmd->redir)
// 		handle_redir(cmd->redir, fd_in, fd_out);
// }

void	execute3(t_shell *shell)
{
	t_cmds	*curr;
	int		prev_fd;

	prev_fd = -1;
	curr = shell->cmds;
	if (execute_builtin(curr, shell))
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
