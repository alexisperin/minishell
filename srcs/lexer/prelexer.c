/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:46:57 by aperin            #+#    #+#             */
/*   Updated: 2023/02/01 17:50:12 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_quotes(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && (i == 0 || str[i - 1] != '\\'))
		{
			while (str[i + 1])
			{
				if (str[i + 1] == c && str[i] != '\\')
					break ;
				i++;
			}
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
	if (!valid_quotes(str, '\"') || !valid_quotes(str, '\''))
	{
		print_error(2);
		return (false);
	}
	return (true);
}
