/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/02/01 09:06:23 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_lexer(t_lexer *lexer) // TO REMOVE
{
	while (lexer)
	{
		if (lexer->word)
			printf("%s\n", lexer->word);
		else
			printf("token: %d\n", lexer->token);
		lexer = lexer->next;
	}
}

void	read_input(void)
{
	char	*str;
	t_lexer	*lexer;
	// t_cmds	*cmds;

	str = readline("~$ ");
	lexer = get_lexer(str);
	if (lexer)
	{
		print_lexer(lexer);
		// cmds = get_cmds(lexer);
		get_cmds(lexer);
		free_lexer(lexer);
	}
	free(str);
}
