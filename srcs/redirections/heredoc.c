/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:48 by aperin            #+#    #+#             */
/*   Updated: 2023/03/07 16:10:01 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*to_expand(char *del, bool *expand)
{
	char	*new_del;
	int		i;
	int		j;

	new_del = ft_malloc(ft_strlen(del) - quote_count(del) + 1);
	i = 0;
	j = 0;
	*expand = true;
	while (del[i])
	{
		if (del[i] != '\'' && del[i] != '\"')
		{
			new_del[j] = del[i];
			j++;
		}
		else
			*expand = false;
		i++;
	}
	new_del[j] = 0;
	free(del);
	return (new_del);
}

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

void	heredoc(t_lexer *heredoc, t_shell *shell)
{
	int		fd;
	bool	expand;

	fd = open(".heredoc.tmp", O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror("heredoc");
		exit(1);
	}
	heredoc->word = to_expand(heredoc->word, &expand);
	heredoc_loop(fd, heredoc->word, shell, expand);
	close(fd);
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("heredoc");
		exit(1);
	}
	ft_dup2(fd, STDIN);
	close(fd);
	unlink(".heredoc.tmp");
}
