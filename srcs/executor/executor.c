/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:29:40 by aperin            #+#    #+#             */
/*   Updated: 2023/02/09 09:04:31 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_lexer(t_lexer *lexer); // TO REMOVE

void	print_cmd2(t_cmds *cmds)
{
	int	i;

	printf("--STR--\n");
	i = 0;
	while (cmds->str[i])
	{
		printf("%s\n", cmds->str[i]);
		i++;
	}
	printf("--REDIR--\n");
	print_lexer(cmds->redir);
}

int	execute_cmd(t_cmds *cmd, char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_split(&env[i][5], ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, cmd->str[0]);
		if (access(tmp, F_OK) == 0)
		{
			execve(tmp, cmd->str, env);
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	ft_free_arr(path);
	return (0); // TO update
}

bool	execute_builtin(t_cmds *cmd, char **env)
{
	(void) cmd;
	(void) env;
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		return (ft_pwd());
	// else if (ft_strncmp(cmds->str[0], "echo", 5) == 0)
	// 	return (ft_echo(cmd));
	// else if (ft_strncmp(cmds->str[0], "cd", 3) == 0)
	// 	return (ft_cd(cmd));
	// else if (ft_strncmp(cmds->str[0], "export", 7) == 0)
	// 	return (ft_export(cmd, env));
	// else if (ft_strncmp(cmds->str[0], "unset", 6) == 0)
	// 	return (ft_unset(cmd, env));
	// else if (ft_strncmp(cmds->str[0], "env", 4) == 0)
	// 	return (ft_env(cmd, env));
	// else if (ft_strncmp(cmds->str[0], "exit", 5) == 0)
	// 	return (ft_exit(cmd));
	return (0);
}

void	execute(t_shell *shell)
{
	t_cmds	*curr;
	pid_t	pid;

	curr = shell->cmds;
	while (curr)
	{
		expander(curr, shell->env);
		print_cmd2(curr);
		if (!execute_builtin(curr, shell->env))
		{
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE); // HANDLE ERROR
			if (pid == 0)
				execute_cmd(curr, shell->env);
		}
		curr = curr->next;
	}
}
