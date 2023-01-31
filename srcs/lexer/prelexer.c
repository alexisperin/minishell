/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:46:57 by aperin            #+#    #+#             */
/*   Updated: 2023/01/31 09:51:38 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_quotes(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			while (str[i + 1] && str[i + 1] != '\"')
				i++;
			if (!str[i + 1])
				return (false);
			i++;
		}
		else if (str[i] == '\'')
		{
			while (str[i + 1] && str[i + 1] != '\'')
				i++;
			if (!str[i + 1])
				return (false);
			i++;
		}
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
