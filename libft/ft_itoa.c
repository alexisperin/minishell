/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:30:08 by aperin            #+#    #+#             */
/*   Updated: 2023/03/01 16:57:13 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(long nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

static void	ft_itoa_recursive(long nbr, char *str, int index)
{
	if (nbr > 9)
		ft_itoa_recursive(nbr / 10, str, index - 1);
	str[index] = (nbr % 10) + 48;
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;
	int		i;
	int		len;

	nbr = (long) n;
	len = ft_itoa_len(nbr);
	str = ft_malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = 0;
	i = 0;
	if (nbr < 0)
	{
		str[i] = '-';
		nbr = -nbr;
		i++;
	}
	ft_itoa_recursive(nbr, str, len - 1);
	return (str);
}
