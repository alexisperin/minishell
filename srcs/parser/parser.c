/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:39:33 by aperin            #+#    #+#             */
/*   Updated: 2023/02/01 09:21:22 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_lexer	*add_cmd(t_cmds **cmds, t_lexer *lexer)
{
	t_cmds	*node;
	t_lexer	*tmp;

	node = ft_malloc(sizeof(t_cmds));
	tmp = *lexer;
	while (tmp != end)
	{
		if (tmp->token > 1)
			push_redir(lexer, tmp, node);
		tmp = *lexer;
	}
}

static t_lexer	*split_at_pipe(t_lexer *lexer)
{
	t_lexer	*tmp;
	t_lexer	*new_lexer;

	while (lexer->next && lexer->next->token != P)
		lexer = lexer->next;
	new_lexer = lexer->next;
	lexer->next = NULL;
	if (new_lexer)
	{
		tmp = new_lexer;
		new_lexer = new_lexer->next;
		new_lexer->prev = NULL;
		free(tmp);
	}
	return (new_lexer);
}

t_cmds	*get_cmds(t_lexer *lexer)
{
	t_cmds	*cmds;
	t_lexer	*tmp;

	cmds = NULL;
	while (lexer)
	{
		tmp = split_at_pipe(lexer);
		add_cmd(&cmds, lexer);
		lexer = tmp;
	}
	return (cmds);
}
