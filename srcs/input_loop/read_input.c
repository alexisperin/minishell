/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:29:58 by aperin            #+#    #+#             */
/*   Updated: 2023/01/28 16:03:16 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	read_input(void)
{
	char	*line;
	char	*tmp;

	tmp = readline("$ ");
	line = ft_strtrim(tmp, " ");
	free(tmp);
	if (ft_strncmp(line, "exit", 5) == 0)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	if (valid_quotes(line))
		printf("%s\n", line);
	free(line);
}
