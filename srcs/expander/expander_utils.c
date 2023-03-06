/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:44:57 by aperin            #+#    #+#             */
/*   Updated: 2023/03/06 16:05:48 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	quote_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i += next_quote(str, i);
			count += 2;
		}
		i++;
	}
	return (count);
}

int	var_len(char *str, int len, char **env)
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

int	key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}

int	get_expanded_size(char *str, t_shell *shell)
{
	int		size;
	int		i;
	int		len;
	int		ret;
	char	*return_value;

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
			if (str[i + 1] == '?')
			{
				len = 2;
				return_value = ft_itoa(shell->return_value);
				size += ft_strlen(return_value) - 1;
				free(return_value);
			}
			else
			{
				len = key_len(&str[i]);
				ret = var_len(&str[i], len, shell->env);
				if (ret == 0)
					ret = var_len(&str[i], len, shell->local_env);
				size += ret - 1;
			}
			i += len - 1;
		}
		size++;
		i++;
	}
	return (size - quote_count(str));
}
