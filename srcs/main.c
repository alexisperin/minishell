/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:56:19 by aperin            #+#    #+#             */
/*   Updated: 2023/03/05 16:16:36 by aburnott         ###   ########.fr       */
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
	shell.return_value = 0;
	shell.local_env = 0;
	display_header();
	while (1)
		read_input(&shell);
	return (0);
}
