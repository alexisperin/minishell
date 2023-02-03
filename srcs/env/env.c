/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:12:12 by aperin            #+#    #+#             */
/*   Updated: 2023/02/03 09:22:36 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"
#include "libft.h"

static t_env	*new_node(char *var)
{
	
}

t_env	*ft_getenv(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (!env)
			env = new_node(envp[i]);
		else
		{
			tmp = env;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_node(envp[i]);
		}
		i++;
	}
}
