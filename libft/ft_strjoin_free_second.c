/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_second.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:30:26 by aperin            #+#    #+#             */
/*   Updated: 2023/03/12 21:01:22 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_second(char *s1, char *s2)
{
	size_t	len;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((len + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	free(s2);
	return (join);
}
