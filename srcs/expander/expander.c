/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:11:53 by aperin            #+#    #+#             */
/*   Updated: 2023/03/06 14:20:46 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	copy_variable(char *str, char *new_str, int *j, t_shell * shell)
{
	int		i;
	int		len;
	char	*return_value;

	if (ft_strncmp(str, "$?", 2) == 0)
	{
		return_value = ft_itoa(shell->return_value);
		ft_strlcpy(&new_str[*j], return_value, ft_strlen(return_value) + 1);
		*j += ft_strlen(return_value);
		free(return_value);
		return (2);
	}
	i = 0;
	len = key_len(str);
	while (shell->env[i])
	{
		if (ft_strncmp(&str[1], shell->env[i], len - 1) == 0
			&& shell->env[i][len - 1] == '=')
			break ;
		i++;
	}
	if (shell->env[i])
	{
		ft_strlcpy(&new_str[*j], &shell->env[i][len],
					ft_strlen(&shell->env[i][len]) + 1);
		*j += ft_strlen(&shell->env[i][len]);
	}
	return (len);
}

static char	*expand_str(char *str, t_shell *shell)
{
	int		size;
	int		i;
	int		j;
	char	*new_str;
	bool	in_quote;

	size = get_expanded_size(str, shell);
	new_str = ft_malloc((size + 1) * sizeof(char));
	i = 0;
	j = 0;
	in_quote = false;
	while (str[i])
	{
		if (str[i] == '\"')
			in_quote = !in_quote;
		else if (str[i] == '\'' && !in_quote)
		{
			i++;
			while (str[i] != '\'')
				new_str[j++] = str[i++];
		}
		else if (str[i] == '$')
			i += copy_variable(&str[i], new_str, &j, shell) - 1;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = 0;
	free(str);
	return (new_str);
}

void	expander(t_shell *shell)
{
	t_cmds	*tmp;
	t_lexer	*tmp2;
	int		i;

	tmp = shell->cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			tmp->str[i] = expand_str(tmp->str[i], shell);
			i++;
		}
		tmp2 = tmp->redir;
		while (tmp2)
		{
			if (tmp2->token != 0 && tmp2->token != LL)
				tmp2->next->word = expand_str(tmp2->next->word, shell);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
