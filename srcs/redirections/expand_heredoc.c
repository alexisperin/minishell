/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:08:55 by aperin            #+#    #+#             */
/*   Updated: 2023/03/07 16:09:57 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	print_var(char *var_name, t_shell *shell, int fd)
{
	int		var_len;
	int		i;
	char	*ret;

	if (ft_strncmp(var_name, "$?", 2) == 0)
	{
		free(var_name);
		ret = ft_itoa(shell->return_value);
		write(fd, ret, ft_strlen(ret));
		free(ret);
		return ;
	}
	i = 0;
	var_len = ft_strlen(var_name);
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(&var_name[1], shell->env[i], var_len - 1) == 0
			&& shell->env[i][var_len - 1] == '=')
		{
			write(fd, &shell->env[i][var_len],
				ft_strlen(&shell->env[i][var_len]));
		}
		i++;
	}
	free(var_name);
}

void	expand_heredoc(char *str, int fd, t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] != '$')
			j++;
		write(fd, &str[i], j);
		i += j;
		if (str[i] == '$')
		{
			j = 0;
			if (str[i + 1] == '?')
				j = 2;
			else
				while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\"'
					&& str[i + j] != '\'')
					j++;
			print_var(ft_substr(&str[i], 0, j), shell, fd);
			i += j;
		}
	}
}
