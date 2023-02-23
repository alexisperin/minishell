/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:04:29 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/23 16:26:32 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_pwd(void)
{
	char	*pwd;
	
	pwd = malloc(sizeof(*pwd) * PATH_MAX);
	if (!pwd)
		return (NULL);
	if (getcwd(pwd, PATH_MAX))
		return (pwd);
	else
		return (NULL);
}

int	add_path(t_shell *shell, char *temp)
{
	int		i;
	int		old;
	char	*pwd;

	i = 0;
	old = 1;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD", 3) == 0)
		{
			free(shell->env[i]);
			pwd = get_pwd();
			if (!pwd)
				return (-1);
			shell->env[i] = ft_strjoin("PWD=", pwd);
		}
		else if (ft_strncmp(shell->env[i], "OLDPWD=", 6) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", temp);
			old = 0;
		}
		i++;
	}
	if (old)
	{
		//export function to create OLDPWD
		return (-1);
	}
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
			return (ft_substr(shell->env[i], path_len, ft_strlen(shell->env[i]) - path_len));
		i++;
	}
	return (0);
}

int	change_path(char *path, t_shell *shell, int type)
{
	char	*path_extract;
	int	ret;
	char	*current_pwd;

	ret = 0;
	current_pwd = get_pwd();
	if (type == 1)
	{
		path_extract = extract_path(path, shell);
		if (!path_extract)
			return (2);
		ret = chdir(path_extract);
		if (ret < 0)
			printf("\n\nFAILED CHDIR 45\n");
		else
			add_path(shell, current_pwd);
	}
	else if (type == 2)
	{
		ret = chdir(path);
		if (ret < 0)
			printf("\n\nFAILED CHDIR 50\n");
		else
			add_path(shell, current_pwd);
	}
	return (1);
}

int	ft_cd(t_cmds *cmd, t_shell *shell)
{
	// int	ret;

	// ret = 1;
	if (!cmd->str[1])
		change_path("HOME=", shell, 1);
	else if (cmd->str[1])
	{
		if (ft_strncmp(cmd->str[1], "-", 1) == 0)
		{
			if (change_path("OLDPWD=", shell, 1) == 2)
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		}
		else
			change_path(cmd->str[1], shell, 2);
	}
	return (1);
}
