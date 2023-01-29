/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:08:56 by aperin            #+#    #+#             */
/*   Updated: 2023/01/29 16:23:07 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	substr_len;
	char	*substr;

	if (!s)
		return (0);
	if (!len || ft_strlen(s) <= start)
		return (ft_strdup(""));
	substr_len = ft_strlen(s + start);
	if (substr_len > len)
		substr_len = len;
	substr = ft_malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}
