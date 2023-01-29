/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:22:14 by aperin            #+#    #+#             */
/*   Updated: 2023/01/29 16:36:28 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

t_token	get_token(char *str)
{
	if (str[0] == '|')
		return (P);
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (LL);
		else
			return (L);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (RR);
		else
			return (R);
	}
	return (0);
}

void	lexer_add_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*tmp;

	if (!(*lexer))
		*lexer = new;
	else
	{
		tmp = *lexer;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->word);
		free(tmp);
	}
}