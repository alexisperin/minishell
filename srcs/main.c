/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:56:19 by aperin            #+#    #+#             */
/*   Updated: 2023/01/27 10:54:59 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	display_header(void)
{
	printf("%s/* *************************************************************\
************* */\n\
/*                                                                            \
*/\n\
/*                                                        :::      ::::::::   \
*/\n\
/*   Minishell                                          :+:      :+:    :+:   \
*/\n\
/*                                                    +:+ +:+         +:+     \
*/\n\
/*   By: aperin & aburnott                          +#+  +:+       +#+        \
*/\n\
/*                                                +#+#+#+#+#+   +#+           \
*/\n\
/*                                                     #+#    #+#             \
*/\n\
/*   As beautiful as a shell                          ###   ########.fr       \
*/\n\
/*                                                                            \
*/\n\
/* ************************************************************************** \
*/%s\n", MAG, NRM);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	if (ac > 1)
		print_error(1);
	(void) av;
	(void) envp;
	display_header();
	while (1)
	{
		line = readline("$ ");
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		free(line);
	}
	return (0);
}
