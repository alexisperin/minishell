/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/03/14 16:54:52 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	read_input(t_shell *shell)
{
	char	*str;
	t_lexer	*lexer;

	sig_handler(0);
	str = readline(PROMPT);
	if (!str)
		ft_exit(NULL);
	if (prelexer_check(str))
	{
		lexer = get_lexer(str);
		if (lexer && postlexer_check(lexer))
		{
			lexer = expand(lexer, shell);
			shell->cmds = get_cmds(lexer);
			g_return_value = 0;
			execute(shell);
			free_cmds(shell->cmds);
		}
	}
	if (ft_strlen(str) != 0)
		add_history(str);
	free(str);
}
