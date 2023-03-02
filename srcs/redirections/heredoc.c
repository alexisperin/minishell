/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:48 by aperin            #+#    #+#             */
/*   Updated: 2023/03/02 14:58:08 by aperin           ###   ########.fr       */
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

static void	heredoc_loop(int fd, char *delimitor)
{
	int 	delimitor_len;
	char	*str;

	delimitor_len = ft_strlen(delimitor);
	while (19)
	{
		str = readline("> ");
		if (!str)
		{
			heredoc_eof(delimitor);
			break ;
		}
		if (ft_strncmp(delimitor, str, delimitor_len + 1) == 0)
			break ;
		// str = expand_heredoc(str); TO DO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
}

void	heredoc(char *delimitor)
{
	int		fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror("heredoc");
		exit(1); // TO UPDATE
	}
	heredoc_loop(fd, delimitor);
	close(fd);
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("heredoc");
		exit(1); // TO UPDATE
	}
	ft_dup2(fd, STDIN);
	close(fd);
	unlink(".heredoc.tmp");
}