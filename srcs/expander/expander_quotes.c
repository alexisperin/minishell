/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:12:54 by aperin            #+#    #+#             */
/*   Updated: 2023/03/16 12:26:42 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_var(char *str, int *index, t_shell *shell)
{
	int	i;
	int	j;

	if (str[1] == '?')
	{
		*index += 2;
		return (ft_itoa(g_return_value));
	}
	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	*index += i;
	j = 0;
	while (shell->env[j])
	{
		if (ft_strncmp(&str[1], shell->env[j], i - 1) == 0
			&& shell->env[j][i - 1] == '=' && shell->env[j][i])
			return (&shell->env[j][i]);
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

static char	*in_quotes(char *exp_str, char *str, int *index, t_shell *shell)
{
	char	*var;

	var = get_var(str, index, shell);
	exp_str = ft_strjoin_free(exp_str, var);
	if (str[1] == '?')
		free(var);
	return (exp_str);
}

char	*double_quotes(char *exp_str, char *str, int *index, t_shell *shell)
{
	int		i;
	int		j;

	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
			exp_str = in_quotes(exp_str, &str[i], &i, shell);
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
	if (i == 1)
		return (ft_strjoin_free(exp_str, ""));
	return (exp_str);
}
