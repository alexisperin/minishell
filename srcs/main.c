/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:56:19 by aperin            #+#    #+#             */
/*   Updated: 2023/02/27 16:01:28 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_env(char **env)
{
	int i = 0;
	
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void) av;
	if (ac > 1)
	{
		print_error(1);
		return (-1);
	}
	shell.env = ft_arrdup(envp);
	sig_handler();
	display_header();
	while (1)
		read_input(&shell);
	return (0);
}
