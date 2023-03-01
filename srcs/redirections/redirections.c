/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:58:12 by aperin            #+#    #+#             */
/*   Updated: 2023/03/01 16:03:12 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redir_output(char *file, t_token token)
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
	return (true);
}

static bool	redir_input(char *file)
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
	return (true);
}

bool	handle_redirections(t_cmds *cmd)
{
	t_lexer	*curr;

	curr = cmd->redir;
	while (curr)
	{
		if (curr->token == L && !redir_input(curr->next->word))
			return (false);
		else if ((curr->token == R || curr->token == RR)
			&& !redir_output(curr->next->word, curr->token))
			return (false);
		curr = curr->next;
	}
	return (true);
}
