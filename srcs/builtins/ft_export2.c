/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:04:30 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/10 13:42:57 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] != '=' && str[i])
	{
		if (!is_identifier(str[i]) || (str[i] == '=' && i == 0))
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (2);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	check_and_send(t_shell *shell, char *str)
{
	int	check;
	int	identifier;

	check = 0;
	identifier = check_identifier(str);
	if (!identifier)
		check = export_err(str);
	else if (!check_validity(str))
		check = 1;
	else if (if_exist(shell->env, str))
		check = 1;
	else
	{
		if (!check)
		{
			if (identifier == 2)
				join_arr(shell, str);
			else
				send_arr(shell, str);
		}
	}
}

char	*little_copy(char *str, int len)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_malloc(len);
	while (str[len])
	{
		temp[i] = str[len];
		i++;
		len++;
	}
	return (temp);
}
