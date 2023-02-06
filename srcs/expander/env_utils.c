/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:11:14 by aperin            #+#    #+#             */
/*   Updated: 2023/02/05 16:41:46 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = key_len(key);
	while (env[i])
	{
		if (ft_strncmp(key, env[i], len) == 0 && key[len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}
