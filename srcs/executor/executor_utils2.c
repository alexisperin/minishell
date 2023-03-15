/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:15:42 by aperin            #+#    #+#             */
/*   Updated: 2023/03/15 10:26:42 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_execve(t_cmds *cmd, t_shell *shell, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path && path[i])
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
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd->str[0], STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
	exit(127);
}

void	ft_waitpid(t_shell *shell)
{
	t_cmds	*curr;
	int		status;
	int		sig;

	curr = shell->cmds;
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			g_return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				g_return_value = 130;
			else if (sig == SIGQUIT)
				g_return_value = 131;
		}
		if (g_return_value == 130 || g_return_value == 131)
			shell->stop = true;
		curr = curr->next;
	}
}

bool	single_cmd(t_shell *shell)
{
	int		save_stdin;
	int		save_stdout;

	if (is_builtin(shell->cmds))
	{
		save_stdin = ft_dup(STDIN);
		save_stdout = ft_dup(STDOUT);
		if (handle_redirections(shell->cmds, shell))
			execute_builtin(shell->cmds, shell);
		ft_dup2(save_stdin, STDIN);
		ft_dup2(save_stdout, STDOUT);
		return (true);
	}
	return (false);
}
