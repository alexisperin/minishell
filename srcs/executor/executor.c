/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:29:40 by aperin            #+#    #+#             */
/*   Updated: 2023/02/07 08:26:35 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_lexer *lexer); // TO REMOVE

void	print_cmd2(t_cmds *cmds)
{
	int	i;

	printf("--STR--\n");
	i = 0;
	while (i < cmds->size)
	{
		printf("%s\n", cmds->str[i]);
		i++;
	}
	printf("--REDIR--\n");
	print_lexer(cmds->redir);
}

void	execute(t_shell *shell)
{
	
	expander(shell->cmds, shell->env);
	print_cmd2(shell->cmds);
}
