/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:56:19 by aperin            #+#    #+#             */
/*   Updated: 2023/02/03 09:11:32 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_env(char **envp)
{
	int	i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	if (ac > 1)
	{
		print_error(1);
		return (-1);
	}
	(void) av;
	(void) envp;
	env = ft_getenv(envp);
	display_header();
	// print_env(envp);
	while (1)
		read_input();
	return (0);
}
