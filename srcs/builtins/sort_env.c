/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:22:18 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/14 14:37:19 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		write(1, "declare -x ", 11);
		j++;
		write(1, env[i], j);
		write(1, "\"", 1);
		while (env[i][j])
		{
			write(1, &env[i][j], 1);
			j++;
		}
		write(1, "\"\n", 2);
		i++;
	}
}

static void	sorter(char **env_sort, int len)
{
	int		i;
	int		j;
	int		min_i;
	char	*temp;

	i = 0;
	while (i < len - 1)
	{
		min_i = i;
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env_sort[j], env_sort[min_i],
					ft_strlen(env_sort[min_i])) < 0)
				min_i = j;
			j++;
		}
		temp = ft_strdup(env_sort[i]);
		free(env_sort[i]);
		env_sort[i] = ft_strdup(env_sort[min_i]);
		free(env_sort[min_i]);
		env_sort[min_i] = ft_strdup(temp);
		free(temp);
		i++;
	}	
}

void	sort_env(t_shell *shell)
{
	char	**env_sort;
	int		len;

	len = 0;
	if (shell->sorted_env != 0)
		ft_free_arr(shell->sorted_env);
	env_sort = ft_arrdup(shell->env);
	while (env_sort[len])
		len++;
	sorter(env_sort, len);
	shell->sorted_env = env_sort;
}
