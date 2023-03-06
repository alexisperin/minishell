/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/06 15:14:12 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"

int	event(void)
{
	printf("TEST\n");
	return (0);
}

void	ctrl_slash(int sig)
{
	(void) sig;
	return ;
}

void	ctrl_c(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	//rl_done = 1;
	return ;
}

void	sig_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ctrl_c;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}