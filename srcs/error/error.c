/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:50:11 by aperin            #+#    #+#             */
/*   Updated: 2023/03/10 13:16:23 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_error(int error_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(NRM, 2);
	if (error_code == 1)
		ft_putstr_fd("too many input arguments\n", 2);
	else if (error_code == 2)
		ft_putstr_fd("unclosed quote\n", 2);
	else if (error_code == 3)
		ft_putstr_fd("syntax error near unexpected token\n", 2);
}

int	export_err(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
