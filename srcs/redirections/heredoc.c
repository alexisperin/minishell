/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:48 by aperin            #+#    #+#             */
/*   Updated: 2023/03/15 08:09:05 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*expand_delimitor2(char *exp_str, char *str, int *index)
{
	int	j;

	j = 1;
	while (str[*index + j] && str[*index + j] != '\"'
		&& str[*index + j] != '\'')
		j++;
	exp_str = ft_strjoin_free2(exp_str, ft_substr(str, *index, j));
	*index += j;
	return (exp_str);
}

static char	*expand_delimitor(char *str, bool *expand)
{
	int		i;
	char	*exp_str;

	i = 0;
	exp_str = NULL;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			exp_str = ft_strjoin_free2(exp_str,
					ft_substr(str, i + 1, next_quote(str, i) - 1));
			i += next_quote(str, i) + 1;
			*expand = false;
		}
		else
			exp_str = expand_delimitor2(exp_str, str, &i);
	}
	free(str);
	return (exp_str);
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

void	heredoc(t_lexer *heredoc, t_cmds *cmd, t_shell *shell)
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
	if (g_return_value == 130 || g_return_value == -1)
		shell->stop = true;
	sig_handler(2);
}
