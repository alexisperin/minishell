/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:54:38 by aperin            #+#    #+#             */
/*   Updated: 2022/10/22 17:07:36 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ptr_dest;
	const char	*ptr_src;
	size_t		i;

	if (!dest && !src)
		return (0);
	ptr_dest = dest;
	ptr_src = src;
	if (ptr_src < ptr_dest)
	{
		while (n)
		{
			ptr_dest[n - 1] = ptr_src[n - 1];
			n--;
		}
	}
	else
	{
		i = -1;
		while (++i < n)
			ptr_dest[i] = ptr_src[i];
	}
	return (dest);
}
