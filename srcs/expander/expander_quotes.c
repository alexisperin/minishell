/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:12:54 by aperin            #+#    #+#             */
/*   Updated: 2023/03/08 17:21:50 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_var(char *str, int *index, char **env)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '$'
		&& str[i] != ' ')
		i++;
	*index += i;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(&str[1], env[j], i - 1) == 0 && env[j][i - 1] == '=')
			return (&env[j][i]);
		j++;
	}
	return (NULL);
}

char	*single_quotes(char *exp_str, char *str, int *index)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	*index += i + 1;
	return (ft_strjoin_free2(exp_str, ft_substr(str, 1, i - 1)));
}

char	*double_quotes(char *exp_str, char *str, int *index, char **env)
{
	int		i;
	int		j;
	char	*var;

	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			var = get_var(&str[i], &i, env);
			exp_str = ft_strjoin_free(exp_str, var);
		}
		else
		{
			j = 0;
			while (str[i + j] && str[i + j] != '\"' && str[i + j] != '$')
				j++;
			exp_str = ft_strjoin_free2(exp_str, ft_substr(str, i, j));
			i += j;
		}
	}
	*index += i + 1;
	return (exp_str);
}
