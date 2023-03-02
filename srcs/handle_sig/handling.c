/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:05:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/02 11:39:47 by aperin           ###   ########.fr       */
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
	// rl_on_new_line();
	// rl_redisplay();
	return ;
}

void	ctrl_c(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//rl_done = 1;
	return ;
}

void	sig_handler(void)
{
	//rl_event_hook = event;
	signal(SIGQUIT, ctrl_slash);
	signal(SIGINT, ctrl_c);
}