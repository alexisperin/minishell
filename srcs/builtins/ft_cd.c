/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:32:32 by aperin            #+#    #+#             */
/*   Updated: 2023/03/13 10:34:29 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	update_pwd(char *pwd, t_shell *shell)
{
	if (pwd)
	{
		pwd = ft_strjoin_free_second("OLDPWD=", pwd);
		ft_export(0, shell, pwd);
		free(pwd);
	}
	pwd = ft_strjoin_free_second("PWD=", ft_getcwd());
	ft_export(0, shell, pwd);
	free(pwd);
}

static int	ft_chdir(char *path, t_shell *shell)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (!pwd && path[0] != '/')
	{
		perror("cd: error retrieving current directory: getcwd: cannot access\
 parent directories");
		return (0);
	}
	if (chdir(path) != 0)
	{
		perror(path);
		free(pwd);
		return (1);
	}
	update_pwd(pwd, shell);
	return (0);
}

static int	cd_minus(t_shell *shell)
{
	int	i;
	int	ret;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("OLDPWD=", shell->env[i], 7) == 0)
			break ;
		i++;
	}
	if (!shell->env[i])
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR);
		return (1);
	}
	ret = ft_chdir(&shell->env[i][7], shell);
	if (ret == 0)
		ft_pwd();
	return (ret);
}

static int	cd_home(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("HOME=", shell->env[i], 5) == 0)
			break ;
		i++;
	}
	if (!shell->env[i])
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		return (1);
	}
	return (ft_chdir(&shell->env[i][5], shell));
}

int	ft_cd(t_cmds *cmd, t_shell *shell)
{
	if (!cmd->str[1])
		return (cd_home(shell));
	else if (cmd->str[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR);
		return (1);
	}
	else if (cmd->str[1][0] == '\0')
		return (0);
	else if (ft_strncmp("-", cmd->str[1], 2) == 0)
		return (cd_minus(shell));
	return (ft_chdir(cmd->str[1], shell));
}
