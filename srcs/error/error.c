/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:50:11 by aperin            #+#    #+#             */
/*   Updated: 2023/03/13 16:53:40 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_error(int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (error_code == 1)
		ft_putstr_fd("too many input arguments\n", 2);
	else if (error_code == 2)
		ft_putstr_fd("unclosed quote\n", 2);
	else if (error_code == 3)
		ft_putstr_fd("syntax error near unexpected token\n", 2);
	g_return_value = 1;
}

int	export_err(char *str)
{
	g_return_value = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
