/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:50:11 by aperin            #+#    #+#             */
/*   Updated: 2023/01/27 10:52:56 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error_code)
{
	if (error_code == 1)
		write(2, "Error: Too many input arguments\n", 32);
	exit(EXIT_FAILURE);
}