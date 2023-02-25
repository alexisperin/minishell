/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:05:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/25 11:41:15 by aburnott         ###   ########.fr       */
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
	//rl_event_hook = event;
	signal(SIGQUIT, ctrl_slash);
	signal(SIGINT, ctrl_c);
}