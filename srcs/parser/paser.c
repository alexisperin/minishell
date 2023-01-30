/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:39:33 by aperin            #+#    #+#             */
/*   Updated: 2023/01/30 12:09:05 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*add_cmd(t_cmds **cmds, t_lexer *lexer, t_lexer *end)
{
	
}

t_cmds	parser(t_lexer *lexer)
{
	t_cmds	*cmds;
	t_lexer	*tmp;

	cmds = NULL;
	while (lexer)
	{
		tmp = lexer;
		while (tmp && tmp->token != P)
			tmp = tmp->next;
		lexer = add_cmd(&cmds, lexer, tmp);
	}
}
