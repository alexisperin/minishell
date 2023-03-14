/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 23:52:15 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/14 09:22:09 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_check(const char *str, int *check)
{
	int		i;
	int		sign;
	size_t	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - 48;
	if (sign * res > (size_t) LONG_MAX || sign * res < (size_t) LONG_MIN)
		*check = 1;
	else if (i == 0 || str[i])
		*check = 1;
	return (sign * res);
}
