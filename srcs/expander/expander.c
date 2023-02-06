/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:11:53 by aperin            #+#    #+#             */
/*   Updated: 2023/02/06 18:36:43 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	copy_variable(char *str, char *new_str, int *j, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = key_len(str);
	while (env[i])
	{
		if (ft_strncmp(&str[1], env[i], len - 1) == 0
			&& env[i][len - 1] == '=')
			break ;
		i++;
	}
	if (env[i])
	{
		ft_strlcpy(&new_str[*j], &env[i][len], ft_strlen(&env[i][len]) + 1);
		*j += ft_strlen(&env[i][len]);
	}
	return (len);
}

char	*expand_str(char *str, char **env)
{
	int		size;
	int		i;
	int		j;
	char	*new_str;
	bool	in_quote;

	size = get_expanded_size(str, env);
	new_str = ft_malloc((size + 1) * sizeof(char));
	i = 0;
	j = 0;
	in_quote = false;
	while (str[i])
	{
		if (str[i] == '\"')
			in_quote = !in_quote;
		else if (str[i] == '\'' && !in_quote)
			{
				i++;
				while (str[i] != '\'')
					new_str[j++] = str[i++];
			}
		else if (str[i] == '$')
			i += copy_variable(&str[i], new_str, &j, env) - 1;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = 0;
	free(str);
	return (new_str);
}

void	expander(t_shell *shell)
{
	t_cmds	*tmp;
	t_lexer	*tmp2;
	int		i;

	tmp = shell->cmds;
	while (tmp)
	{
		i = 0;
		while (i < tmp->size)
		{
			tmp->str[i] = expand_str(tmp->str[i], shell->env);
			i++;
		}
		tmp2 = tmp->redir;
		while (tmp2)
		{
			if (tmp2->token == 0)
				tmp2->word = expand_str(tmp2->word, shell->env);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
