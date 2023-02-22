/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:04:29 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/19 23:46:01 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*extract_path(char *path, char **env)
{
	int	i;
	int	path_len;

	i = 0;
	path_len = ft_strlen(path);
	while (env[i])
	{
		if (!ft_strncmp(path, env[i], path_len))
			return (ft_substr(env[i], path_len, ft_strlen(env[i]) - path_len));
		i++;
	}
	return (0);
}

int	change_path(char *path, char **env, int type)
{
	char	*path_extract;
	int	ret;

	ret = 0;
	if (type == 1)
	{
		path_extract = extract_path(path, env);
		if (!path_extract)
			return (0);
		ret = chdir(path_extract);
		if (ret < 0)
			printf("\n\nFAILED CHDIR 45\n");
	}
	if (type == 2)
	{
		ret = chdir(path);
		if (ret < 0)
			printf("\n\nFAILED CHDIR 50\n");
	}
	return (1);
}

int	ft_cd(t_cmds *cmd, char **env)
{
	// int	ret;

	// ret = 1;
	if (!cmd->str[1])
		change_path("HOME=", env, 1);
	else if (cmd->str[1])
		change_path(cmd->str[1], env, 2);
	return (1);
}
