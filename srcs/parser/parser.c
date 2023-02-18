/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:39:33 by aperin            #+#    #+#             */
/*   Updated: 2023/02/16 16:24:16 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_lexer	*push_str(t_lexer *lexer, t_lexer **new_lexer)
{
	t_lexer	*ret;
	t_lexer	*tmp;

	ret = lexer->next;
	lexer->next = NULL;
	if (!*new_lexer)
		*new_lexer = lexer;
	else
	{
		tmp = *new_lexer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lexer;
	}
	return (ret);
}

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

static void	add_cmd(t_cmds **cmds, t_lexer *lexer, int n)
{
	t_cmds	*node;
	t_cmds	*tmp;
	t_lexer	*new_lexer;

	node = new_cmd(n);
	new_lexer = NULL;
	while (lexer)
	{
		if (lexer->token != 0)
			lexer = push_redir(lexer, node);
		else
			lexer = push_str(lexer, &new_lexer);
	}
	list_to_tab(node, new_lexer);
	if (!*cmds)
		*cmds = node;
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
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
	int		n;

	cmds = NULL;
	n = 1;
	while (lexer)
	{
		tmp = split_at_pipe(lexer);
		add_cmd(&cmds, lexer, n);
		lexer = tmp;
		n++;
	}
	return (cmds);
}
