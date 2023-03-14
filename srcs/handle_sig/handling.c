/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:31 by aperin            #+#    #+#             */
/*   Updated: 2023/03/14 14:38:53 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_prompt(int sig)
{
	(void) sig;
	g_return_value = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	prompt_nl(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
}

static void	ctrl_c(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	unlink(HEREDOC);
	exit(130);
}

static void	backslash(int sig)
{
	(void) sig;
	exit(131);
}

void	sig_handler(int status)
{
	if (status == 0)
	{
		signal(SIGINT, &reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 1)
	{
		signal(SIGINT, &prompt_nl);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 2)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, &backslash);
	}
	else
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}
