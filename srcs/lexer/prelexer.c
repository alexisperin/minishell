/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:46:57 by aperin            #+#    #+#             */
/*   Updated: 2023/02/06 18:41:17 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	next_quote_bis(char *str, size_t start, bool *closed_quote)
{
	size_t	i;

	i = 1;
	while (str[start + i])
	{
		if (str[start + i] == str[start])
			return (i);
		i++;
	}
	*closed_quote = false;
	return (0);
}

static bool	valid_quotes(char *str)
{
	size_t	i;
	bool	closed_quote;

	i = 0;
	closed_quote = true;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += next_quote_bis(str, i, &closed_quote);
		if (!closed_quote)
			return (false);
		i++;
	}
	return (true);
}

bool	prelexer_check(char *str)
{
	if (!valid_quotes(str))
	{
		print_error(2);
		return (false);
	}
	return (true);
}
