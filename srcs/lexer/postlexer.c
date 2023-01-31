/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postlexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:50:12 by aperin            #+#    #+#             */
/*   Updated: 2023/01/31 10:20:27 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	token_syntax(t_lexer *lexer)
{
	if (lexer->token != 0)
		return (false);
	while (lexer->next)
	{
		if (lexer->token != 0 && lexer->next->token != 0)
			return (false);
		lexer = lexer->next;
	}
	if (lexer->token != 0)
		return (false);
	return (true);
}

bool	postlexer_check(t_lexer *lexer)
{
	if (!token_syntax(lexer))
	{
		print_error(3);
		return (false);
	}
	return (true);
}
