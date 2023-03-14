/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:56:19 by aperin            #+#    #+#             */
/*   Updated: 2023/03/14 17:18:01 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	set_shlvl(t_shell *shell)
{
	char	*shlvl;
	int		i;
	int		lvl;

	i = 0;
	lvl = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp("SHLVL=", shell->env[i], 6) == 0)
		{
			lvl = ft_atoi(&shell->env[i][6]);
			break ;
		}
		i++;
	}
	if (lvl < 0)
		lvl = 0;
	else
		lvl++;
	shlvl = ft_strdup("SHLVL=");
	shlvl = ft_strjoin_free2(shlvl, ft_itoa(lvl));
	ft_export(NULL, shell, shlvl);
	free(shlvl);
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
	set_shlvl(&shell);
	g_return_value = 0;
	shell.sorted_env = 0;
	display_header();
	while (1)
		read_input(&shell);
	return (0);
}
