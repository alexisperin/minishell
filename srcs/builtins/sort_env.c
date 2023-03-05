/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:22:18 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/05 14:31:17 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	sort_env(t_shell *shell)
{
	char	**env_sort;
	char	*temp;
	int		i;
	int		j;
	int		min_i;
	int		len;
	
	i = 0;
	len = 0;
	if (shell->sorted_env[0] != 0)
		ft_free_arr(shell->sorted_env);
	env_sort = ft_arrdup(shell->env);
	while (env_sort[len])
		len++;
	while (i < len - 1)
	{
		min_i = i;
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env_sort[j], env_sort[min_i], ft_strlen(env_sort[min_i])) < 0)
				min_i = j;
			j++;
		}
		temp = ft_strdup(env_sort[i]);
		env_sort[i] = ft_strdup(env_sort[min_i]);
		env_sort[min_i] = ft_strdup(temp);
		i++;
	}
	shell->sorted_env = env_sort;
}