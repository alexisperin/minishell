/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:13 by aperin            #+#    #+#             */
/*   Updated: 2023/03/08 17:19:54 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	new_node(t_lexer **lexer, t_token token, char *word)
{
	t_lexer	*new_node;

	new_node = ft_malloc(sizeof(t_lexer));
	new_node->token = token;
	new_node->word = word;
	new_node->next = NULL;
	lexer_add_back(lexer, new_node);
}

static char	*copy_raw(char *exp_str, char *str, int *index)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
		i++;
	*index += i;
	return (ft_strjoin_free2(exp_str, ft_substr(str, 0, i)));
}

static char	*join_variable(char *exp_str, char *var, t_lexer **lexer)
{
	char	**splitted_var;
	int		i;

	splitted_var = ft_split(var, ' ');
	i = 0;
	if (var[0] != ' ')
	{
		exp_str = ft_strjoin_free2(exp_str, splitted_var[0]);
		new_node(lexer, 0, exp_str);
		i = 1;
	}
	while (splitted_var[i] && splitted_var[i + 1])
	{
		new_node(lexer, 0, splitted_var[i]);
		i++;
	}
	exp_str = splitted_var[i];
	free(splitted_var);
	return (exp_str);
}

static void	expand_node(char *str, t_lexer **lexer, char **env)
{
	char	*exp_str;
	char	*var;
	int		i;

	exp_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			exp_str = single_quotes(exp_str, &str[i], &i);
		else if (str[i] == '\"')
			exp_str = double_quotes(exp_str, &str[i], &i, env);
		else if (str[i] == '$')
		{
			var = get_var(&str[i], &i, env);
			if (var)
				exp_str = join_variable(exp_str, var, lexer);
		}
		else
			exp_str = copy_raw(exp_str, &str[i], &i);
	}
	if (exp_str && exp_str[0] != 0)
		new_node(lexer, 0, exp_str);
}

t_lexer	*expand(t_lexer *lexer, char **env)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp;

	new_lexer = NULL;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->token != 0)
			new_node(&new_lexer, tmp->token, tmp->word);
		else
			expand_node(tmp->word, &new_lexer, env);
		tmp = tmp->next;
	}
	free_lexer(lexer);
	return (new_lexer);
}
