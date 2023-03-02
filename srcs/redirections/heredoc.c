/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:48 by aperin            #+#    #+#             */
/*   Updated: 2023/03/02 09:23:23 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	heredoc(char *delimitor)
{
	int		fd;
	int		delimitor_len;
	char	*str;

	fd = open(".heredoc.tmp", O_RDWR | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror("heredoc");
		exit(1); // TO UPDATE
	}
	delimitor_len = ft_strlen(delimitor);
	while (19)
	{
		str = readline("> ");
		if (ft_strncmp(delimitor, str, delimitor_len + 1) == 0)
			break ;
		write(fd, str, ft_strlen(str));
	}
	ft_dup2(fd, STDIN);
	close(fd);
	// unlink(".heredoc.tmp");
}