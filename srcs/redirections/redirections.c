/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:58:12 by aperin            #+#    #+#             */
/*   Updated: 2023/03/02 08:41:00 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_output(char *file, t_token token)
{
	int	fd;

	if (token == R)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror(file);
		exit(1); //TO UPDATE ???
	}
	ft_dup2(fd, STDOUT);
	close(fd);
}

static void	redir_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(1); //TO UPDATE ???
	}
	ft_dup2(fd, STDIN);
	close(fd);
}

void	handle_redirections(t_cmds *cmd)
{
	t_lexer	*curr;

	curr = cmd->redir;
	while (curr)
	{
		if (curr->token == L)
			redir_input(curr->next->word);
		else if (curr->token == LL)
			heredoc(curr->next->word);
		else if ((curr->token == R || curr->token == RR))
			redir_output(curr->next->word, curr->token);
		curr = curr->next;
	}
}
