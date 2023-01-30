/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/01/30 15:00:00 by aperin           ###   ########.fr       */
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
	char	*tmp;
	t_lexer	*lexer;

	tmp = readline("~$ ");
	str = ft_strtrim(tmp, " ");
	free(tmp);
	if (ft_strncmp(str, "exit", 5) == 0)
	{
		free(str);
		exit(EXIT_SUCCESS);
	}
	lexer = get_lexer(str);
	if (lexer)
	{
		print_lexer(lexer);
		free_lexer(lexer);
	}
	free(str);
}
