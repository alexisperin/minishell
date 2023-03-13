/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buil_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:16:49 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/13 10:35:31 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	join_path(t_shell *shell, int i, char *temp, char *str)
{
	char	*pwd;

	pwd = 0;
	if (!temp)
	{
		pwd = ft_getcwd();
		free(shell->env[i]);
		shell->env[i] = ft_strjoin(str, pwd);
		free(pwd);
	}
	else
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin(str, temp);
	}
}

int	check_validity(char *str)
{
	int	i;
	int	equ;

	i = 0;
	equ = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equ = 1;
		i++;
	}
	return (equ);
}

int	is_identifier(char c)
{
	if (c == '|' || c == '<' || c == '>'
		|| c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' '
		|| c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{'
		|| c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#'
		|| c == '@' || c == '!'
		|| c == '~' || c == '-'
		|| c == '?' || c == '&' || c == '*')
		return (0);
	return (1);
}
