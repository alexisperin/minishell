/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:57:40 by aperin            #+#    #+#             */
/*   Updated: 2022/10/22 17:53:07 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	casted_c;

	i = 0;
	casted_c = c;
	while (s[i])
		i++;
	while (i > 0 && s[i] != casted_c)
		i--;
	if (s[i] == casted_c)
		return ((char *) s + i);
	return (0);
}
