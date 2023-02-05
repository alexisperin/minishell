/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:11:53 by aperin            #+#    #+#             */
/*   Updated: 2023/02/05 15:52:13 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_variable(char *str, char *new_str, int *j, char **env)
{
	int		i;
	char	*var;

	while
}

static char	*expand_str(char *str, char **env)
{
	int		size;
	int		i;
	int		j;
	char	*new_str;

	size = get_expanded_size(str, env);
	new_str = ft_malloc(size * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			{
				i++;
				while (str[i] != '\'')
					new_str[j++] = str[i++];
			}
		else if (str[i] == '$')
			i += copy_variable(&str[i], new_str, &j, env);
		else if (str[i] != '\"')
			new_str[j++] = str[i];
		i++;
	}
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
