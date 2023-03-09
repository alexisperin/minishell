/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/03/09 09:54:24 by aperin           ###   ########.fr       */
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

void	print_cmd(t_cmds *cmds) //TO REMOVE
{
	int	i;

	printf("----CMDS----\n");
	while (cmds)
	{
		printf("--STR %d--\n", cmds->n);
		i = 0;
		while (cmds->str[i])
		{
			printf("%s\n", cmds->str[i]);
			i++;
		}
		printf("--REDIR %d--\n", cmds->n);
		print_lexer(cmds->redir);
		cmds = cmds->next;
	}
	printf("----------------------\n");
}

void	read_input(t_shell *shell)
{
	char	*str;
	t_lexer	*lexer;

	str = readline(PROMPT);
	if (!str)
		ft_exit(NULL, 1);
	if (prelexer_check(str))
	{
		lexer = get_lexer(str);
		if (lexer && postlexer_check(lexer))
		{
			// print_lexer(lexer);
			lexer = expand(lexer, shell);
			// print_lexer(lexer);
			shell->cmds = get_cmds(lexer);
			// print_cmd(shell->cmds);
			execute(shell);
			free_cmds(shell->cmds);
		}
	}
	if (ft_strlen(str) != 0)
		add_history(str);
	free(str);
}
