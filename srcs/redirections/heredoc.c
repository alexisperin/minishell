/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:48 by aperin            #+#    #+#             */
/*   Updated: 2023/03/07 13:11:31 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*get_var(char *var_name, t_shell *shell)
{
	int	var_len;
	int	i;

	if (ft_strncmp(var_name, "$?", 2) == 0)
	{
		free(var_name);
		return (ft_itoa(shell->return_value));
	}
	i = 0;
	var_len = ft_strlen(var_name);
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(&var_name[1], shell->env[i], var_len - 1) == 0
			&& shell->env[i][var_len - 1] == '=')
		{
			free(var_name);
			return (ft_strdup(&shell->env[i][var_len]));
		}
		i++;
	}
	free(var_name);
	return (NULL);
}

static void	expand_heredoc(char *str, int fd, t_shell *shell)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] != '$')
			j++;
		write(fd, &str[i], j);
		i += j;
		if (str[i] == '$')
		{
			j = 0;
			if (str[i + 1] == '?')
				j = 2;
			else
				while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\"'
					&& str[i + j] != '\'')
					j++;
			var = get_var(ft_substr(&str[i], 0, j), shell);
			write(fd, var, ft_strlen(var));
			free(var);
			i += j;
		}
	}
	write(fd, "\n", 1);
}

static void	heredoc_eof(char *delimitor)
{
	rl_replace_line("", 0);
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `",
				STDERR);
	ft_putstr_fd(delimitor, STDERR);
	ft_putstr_fd("')\n", STDERR);
}

static void	heredoc_loop(int fd, char *delimitor, t_shell *shell)
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
			return ;
		}
		if (ft_strncmp(delimitor, str, delimitor_len + 1) == 0)
			break ;
		expand_heredoc(str, fd, shell);
		free(str);
	}
	free(str);
}

void	heredoc(char *delimitor, t_shell *shell)
{
	int		fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror("heredoc");
		exit(1);
	}
	heredoc_loop(fd, delimitor, shell);
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