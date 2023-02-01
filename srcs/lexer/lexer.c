/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:32:25 by aperin            #+#    #+#             */
/*   Updated: 2023/02/01 17:58:50 by aperin           ###   ########.fr       */
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

static int	add_word(char *str, t_lexer **lexer)
{
	t_lexer	*node;
	size_t	i;

	i = 0;
	node = ft_malloc(sizeof(t_lexer));
	node->token = 0;
	node->prev = NULL;
	node->next = NULL;
	while (str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>')
		i++;
	node->word = ft_substr(str, 0, i);
	lexer_add_back(lexer, node);
	return (ft_strlen(node->word));
}

t_lexer	*get_lexer(char *str)
{
	t_lexer	*lexer;
	size_t	i;

	lexer = NULL;
	i = 0;
	if (!str || !prelexer_check(str))
		return (NULL);
	while (str[i])
	{
		i += skip_spaces(&str[i]);
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i += add_token(&str[i], &lexer);
		else if (str[i])
			i += add_word(&str[i], &lexer);
	}
	if (!postlexer_check(lexer))
	{
		free_lexer(lexer);
		return (NULL);
	}
	return (lexer);
}
