/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:44:57 by aperin            #+#    #+#             */
/*   Updated: 2023/02/03 17:27:50 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	var_len(char *str, int len, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(&str[1], env[i], len - 1) == 0
			&& env[i][len - 1] == '=')
			return (ft_strlen(&env[i][len]));
		i++;
	}
	return (0);
}

static int	key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}

int	get_expanded_size(char *str, char **env)
{
	int	size;
	int	i;
	int	len;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			len = next_quote(str, i);
			i += len;
			size += len;
		}
		else if (str[i] == '$')
		{
			len = key_len(&str[i]);
			size += var_len(&str[i], len, env) - 1;
			i += len - 1;
		}
		size++;
		i++;
	}
	return (size);
}
