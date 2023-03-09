/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:04:29 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/09 15:13:08 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	add_path(t_shell *shell, char *temp)
{
	int		i;
	int		old;
	int		p;

	i = 0;
	old = 1;
	p = 2;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD", 3) == 0)
		{
			join_path(shell, i, 0, "PWD=");
			p = 0;
		}
		else if (ft_strncmp(shell->env[i], "OLDPWD=", 6) == 0)
		{
			join_path(shell, i, temp, "OLDPWD=");
			old = 0;
		}
		i++;
	}
	if (old || p)
		modify_path(shell, temp, old, p);
	return (0);
}

char	*extract_path(char *path, t_shell *shell)
{
	int	i;
	int	path_len;

	i = 0;
	path_len = ft_strlen(path);
	while (shell->env[i])
	{
		if (!ft_strncmp(path, shell->env[i], path_len))
			return (ft_substr(shell->env[i], path_len,
					ft_strlen(shell->env[i]) - path_len));
		i++;
	}
	return (0);
}

int	change_path(char *path, t_shell *shell, int type)
{
	char	*path_extract;
	int		ret;
	char	*current_pwd;

	current_pwd = get_pwd();
	if (type == 1)
	{
		path_extract = extract_path(path, shell);
		ret = chdir(path_extract);
		if (ret < 0)
			return (0);
		else
			add_path(shell, current_pwd);
		free(path_extract);
	}
	else if (type == 2)
	{
		ret = chdir(path);
		if (ret < 0)
			return (0);
		else
			add_path(shell, current_pwd);
	}
	free(current_pwd);
	return (1);
}

int	sending(t_cmds *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->str[1], "-", 1) == 0)
	{
		if (!change_path("OLDPWD=", shell, 1))
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			printf("%s\n", extract_path("PWD=", shell));
	}
	else
	{
		if (!change_path(cmd->str[1], shell, 2))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(cmd->str[1]);
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_cmds *cmd, t_shell *shell)
{
	if (!cmd->str[1])
	{
		if (!change_path("HOME=", shell, 1))
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else if (cmd->str[1][0] == '\0')
		return (0);
	else if (cmd->str[1] && cmd->str[2] != 0)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (0);
	}
	else if (cmd->str[1])
	{
		if (sending(cmd, shell))
			return (0);
	}
	return (0);
}
