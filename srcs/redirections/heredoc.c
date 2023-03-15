/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:48 by aperin            #+#    #+#             */
/*   Updated: 2023/03/15 10:53:31 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	heredoc_eof(char *delimitor)
{
	rl_replace_line("", 0);
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `",
		STDERR);
	ft_putstr_fd(delimitor, STDERR);
	ft_putstr_fd("')\n", STDERR);
}

static void	heredoc_loop(int fd, char *delimitor, t_shell *shell, bool expand)
{
	int		delimitor_len;
	char	*str;

	delimitor_len = ft_strlen(delimitor);
	while (19)
	{
		str = readline("> ");
		if (!str)
		{
			heredoc_eof(delimitor);
			return ;
		}
		if (ft_strncmp(delimitor, str, delimitor_len + 1) == 0)
			break ;
		if (expand)
			expand_heredoc(str, fd, shell);
		else
			write(fd, str, ft_strlen(str));
		free(str);
		write(fd, "\n", 1);
	}
	free(str);
}

static void	heredoc2(t_lexer *heredoc, t_cmds *cmd, t_shell *shell)
{
	int		fd;
	bool	expand;

	sig_handler(3);
	fd = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror(cmd->heredoc);
		exit(-1);
	}
	expand = true;
	heredoc->word = expand_delimitor(heredoc->word, &expand);
	heredoc_loop(fd, heredoc->word, shell, expand);
	close(fd);
	exit(0);
}

static void	heredoc(t_lexer *heredoc, t_cmds *cmd, t_shell *shell)
{
	int		pid;
	int		status;

	cmd->heredoc = heredoc_name(cmd);
	pid = ft_fork();
	if (pid == 0)
		heredoc2(heredoc, cmd, shell);
	sig_handler(4);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_return_value = WEXITSTATUS(status);
	if (g_return_value != 0)
		shell->stop = true;
}

void	handle_heredocs(t_shell *shell)
{
	t_cmds	*curr;
	t_lexer	*lex;

	curr = shell->cmds;
	while (curr && !shell->stop)
	{
		lex = curr->redir;
		while (lex && !shell->stop)
		{
			if (lex->token == LL)
				heredoc(lex->next, curr, shell);
			lex = lex->next;
		}
		curr = curr->next;
	}
}
