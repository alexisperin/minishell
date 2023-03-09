/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:00:11 by aperin            #+#    #+#             */
/*   Updated: 2023/03/08 12:23:48 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dup;

	if (!str)
		return (0);
	len = ft_strlen(str);
	dup = ft_malloc((len + 1) * sizeof(char));
	ft_strlcpy(dup, str, len + 1);
	return (dup);
}
