/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buil_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:16:49 by aburnott          #+#    #+#             */
/*   Updated: 2023/02/26 11:24:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int modify_path(t_shell *shell, char *temp, int code, int code2)
{
    if (code)
        ft_export(0, shell, "OLDPWD=");
    else if (code2)
	{
        ft_export(0, shell, "PWD=");
	}
	add_path(shell, temp);
    return (0);
}

char	*get_pwd(void)
{
	char	*pwd;
	
	pwd = malloc(sizeof(*pwd) * PATH_MAX);
	if (!pwd)
		return (NULL);
	if (getcwd(pwd, PATH_MAX))
		return (pwd);
	else
		return (NULL);
}