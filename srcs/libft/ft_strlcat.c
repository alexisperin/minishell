/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:45:07 by aperin            #+#    #+#             */
/*   Updated: 2022/10/12 10:34:46 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	i;

	if (size < 1)
		return (ft_strlen(src));
	dst_size = ft_strlen(dst);
	if (size < dst_size)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && (dst_size + i) < (size - 1))
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = 0;
	return (dst_size + ft_strlen(src));
}
