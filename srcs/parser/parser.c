/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:39:33 by aperin            #+#    #+#             */
/*   Updated: 2023/02/01 11:19:06 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_lexer	*push_redir(t_lexer *redir, t_cmds *cmd)
{
	t_lexer	*ret;
	t_lexer	*tmp;

	ret = redir->next->next;
	redir->next->next = NULL;
	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	return (ret);
}

static void	add_cmd(t_cmds **cmds, t_lexer *lexer)
{
	t_cmds	*node;
	t_lexer	*tmp;
	t_cmds	*tmp2;

	node = ft_malloc(sizeof(t_cmds));
	node->redir = NULL;
	tmp = lexer;
	while (tmp)
	{
		while (tmp->next && tmp->next->token == 0)
			tmp = tmp->next;
		if (tmp->next)
			tmp->next = push_redir(tmp->next, node);
	}
	get_command(node, )
	if (!*cmds)
		*cmds = node;
	else
	{
		tmp2 = *cmds;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = node;
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
