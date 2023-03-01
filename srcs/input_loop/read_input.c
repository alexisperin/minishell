/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/02/28 10:14:57 by aperin           ###   ########.fr       */
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
}

void	read_input(t_shell *shell)
{
	char	*str;
	t_lexer	*lexer;

	str = readline("~$ ");
	lexer = get_lexer(str);
	if (lexer)
	{
		shell->cmds = get_cmds(lexer);
		// print_cmd(shell->cmds);
		expander(shell);
		// print_cmd(shell->cmds);
		execute(shell);
		free_cmds(shell->cmds);
	}
	if (!str)
		ft_exit(NULL, 1);
	if (ft_strlen(str) != 0)
		add_history(str);
	free(str);
}
