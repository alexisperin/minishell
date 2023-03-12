/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:30:23 by aperin            #+#    #+#             */
/*   Updated: 2023/03/12 17:55:31 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_getcwd(void)
{
	char	*buf;

	buf = ft_malloc(PATH_MAX * sizeof(char));
	if (getcwd(buf, PATH_MAX))
		return (buf);
	free(buf);
	return (NULL);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	return (1);
}
