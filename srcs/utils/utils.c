/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:45:59 by aperin            #+#    #+#             */
/*   Updated: 2023/01/30 14:56:27 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_quotes(char *str)
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
