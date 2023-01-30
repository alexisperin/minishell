/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:32:25 by aperin            #+#    #+#             */
/*   Updated: 2023/01/30 10:35:24 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	add_token(char *str, t_lexer **lexer)
{
	t_token	token;
	t_lexer	*new;

	new = ft_malloc(sizeof(t_lexer));
	new->word = NULL;
	token = get_token(str);
	new->token = token;
	new->prev = NULL;
	new->next = NULL;
	lexer_add_back(lexer, new);
	if (token == LL || token == RR)
		return (2);
	return (1);
}

static char	*get_word(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '\"')
	{
		i++;
		while (str[i] != '\"')
			i++;
		i++;
	}
	else if (str[0] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
		i++;
	}
	else
	{
		while (str[i] && (str[i] < 9 || str[i] > 13) && str[i] != 32
			&& str[i] != '\"' && str[i] != '\'')
			i++;
	}
	return (ft_substr(str, 0, i));
}

static int	add_word(char *str, t_lexer **lexer)
{
	t_lexer	*node;

	node = ft_malloc(sizeof(t_lexer));
	node->word = get_word(str);
	node->token = 0;
	node->prev = NULL;
	node->next = NULL;
	lexer_add_back(lexer, node);
	return (ft_strlen(node->word));
}

t_lexer	*get_lexer(char *str)
{
	t_lexer	*lexer;
	size_t	i;

	lexer = NULL;
	i = 0;
	while (str[i])
	{
		i += skip_spaces(&str[i]);
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i += add_token(&str[i], &lexer);
		else
			i += add_word(&str[i], &lexer);
	}
	return (lexer);
}
