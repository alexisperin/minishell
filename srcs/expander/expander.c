/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:11:53 by aperin            #+#    #+#             */
/*   Updated: 2023/02/03 16:02:03 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// static char	*expand_str(char *str, char **env)
// {
// 	int	size;

// 	size = get_expanded_size(str, env);
// }

void	expander(t_shell *shell)
{
	(void) shell;
	// t_cmds	*tmp;
	// t_lexer	*tmp2;
	// int		i;

	// tmp = shell->cmds;
	// while (tmp)
	// {
	// 	i = 0;
	// 	while (i < tmp->size)
	// 	{
	// 		tmp->str[i] = expand_str(tmp->str[i], shell->env);
	// 		i++;
	// 	}
	// 	tmp2 = tmp->redir;
	// 	while (tmp2)
	// 	{
	// 		if (tmp2->token == 0)
	// 			tmp2->word = expand_str(tmp2->word, shell->env);
	// 		tmp2 = tmp2->next;
	// 	}
	// 	tmp = tmp->next;
	// }
}
