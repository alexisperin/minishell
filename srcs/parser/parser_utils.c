/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:10:34 by aperin            #+#    #+#             */
/*   Updated: 2023/02/15 11:51:49 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	list_to_tab(t_cmds *node, t_lexer *lexer)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lexer;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	node->str = ft_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (lexer)
	{
		node->str[i] = lexer->word;
		i++;
		tmp = lexer;
		lexer = lexer->next;
		free(tmp);
	}
	node->str[i] = NULL;
}

void	init_fds(t_cmds *cmds)
{
	int	i;

	i = 1;
	while (cmds)
	{
		cmds->n = i;
		cmds->iofd[0] = STDIN;
		cmds->iofd[1] = STDOUT;
		i++;
		cmds = cmds->next;
	}
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_lexer(tmp->redir);
		i = 0;
		while (tmp->str[i])
		{
			free(tmp->str[i]);
			i++;
		}
		free(tmp->str);
		free(tmp);
	}
}
