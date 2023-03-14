/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:58:12 by aperin            #+#    #+#             */
/*   Updated: 2023/03/14 22:07:08 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_output(char *file, t_token token, pid_t pid)
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
		if (pid == 0)
			exit(1);
		g_return_value = 1;
		return ;
	}
	ft_dup2(fd, STDOUT);
	close(fd);
}

static void	redir_input(char *file, pid_t pid, t_shell *shell)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		if (pid == 0)
			exit(1);
		g_return_value = 1;
		shell->stop = true;
		return ;
	}
	ft_dup2(fd, STDIN);
	close(fd);
}

static void	redir_heredoc(char *heredoc, t_shell *shell)
{
	int	fd;

	fd = open(heredoc, O_RDONLY);
	if (fd == -1)
	{
		g_return_value = 130;
		shell->stop = true;
		return ;
	}
	ft_dup2(fd, STDIN);
	close(fd);
}

bool	handle_redirections(t_cmds *cmd, t_shell *shell)
{
	t_lexer	*curr;

	curr = cmd->redir;
	while (curr && !shell->stop)
	{
		if (curr->token == L)
			redir_input(curr->next->word, cmd->pid, shell);
		else if (curr->token == LL)
			redir_heredoc(cmd->heredoc, shell);
		else if (curr->token == R || curr->token == RR)
			redir_output(curr->next->word, curr->token, cmd->pid);
		curr = curr->next;
	}
	return (!shell->stop);
}
