/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:45:59 by aperin            #+#    #+#             */
/*   Updated: 2023/01/29 16:45:50 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	char_count(char *str, char c)
{
	int		i;
	int		count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			++count;
		++i;
	}
	return (count);
}

bool	valid_quotes(char *str)
{
	if (!str)
		return (false);
	if (char_count(str, '\"') % 2 != 0 || char_count(str, '\'') % 2 != 0)
	{
		print_error(2);
		return (false);
	}
	return (true);
}
