/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/02/02 09:22:18 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_lexer(t_lexer *lexer) // TO REMOVE
{
	if (!lexer)
	{
		printf("NULL\n");
		return ;
	}
	while (lexer)
	{
		if (lexer->word)
			printf("%s\n", lexer->word);
		else
			printf("token: %d\n", lexer->token);
		lexer = lexer->next;
	}
	printf("\n");
}

void	print_cmd(t_cmds *cmds)
{
	int	i = 0;

	printf("----CMDS----\n");
	while (cmds)
	{
		
	}
	printf("\n");
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
	}
	free(str);
}
