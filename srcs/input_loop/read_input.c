/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/02/05 18:00:36 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*expand_str(char *str, char **env); // TO REMOVE

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
	int	i;

	printf("----CMDS----\n");
	while (cmds)
	{
		printf("--STR--\n");
		i = 0;
		while (i < cmds->size)
		{
			printf("%s\n", cmds->str[i]);
			i++;
		}
		printf("--REDIR--\n");
		print_lexer(cmds->redir);
		cmds = cmds->next;
	}
}

void	read_input(t_shell *shell)
{
	char	*str;
	t_lexer	*lexer;

	str = readline("~$ ");
	lexer = get_lexer(str);
	if (lexer)
	{
	printf("%s\n", expand_str(str, shell->env));
		// shell->cmds = get_cmds(lexer);
		// print_cmd(shell->cmds);
		// expander(shell);
		// printf("AFTER EXPANDER\n");
		// print_cmd(shell->cmds);
		// free_cmds(shell->cmds);
	}
	free(str);
}
