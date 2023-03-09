/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.str[i]                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/03/05 14:56:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	if_exist(char **env, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	if (!env)
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len))
		{
			free(env[i]);
			env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_arr(t_shell *shell, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	while(shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], str, len - 2))
			ft_strjoin(shell->env[i], str);
		i++;
	}
}

char	**new_arr(char **env, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(env[i]);
		}
		else
			rtn[i] = ft_strdup(env[i]);
		i++;
	}
	if (!rtn[i])
	{
		ft_free_arr(rtn);
		return (rtn);
	}
	return (rtn);
}

int	send_arr(t_shell *shell, char *str)
{
	int		i;
	char	**rtn;
	
	i = 0;
	while (shell->env[i])
			i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	new_arr(shell->env, rtn, str);
	ft_free_arr(shell->env);
	shell->env = rtn;
	return (1);
}

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '[' || str[i] == ']'
		|| str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == ',' || str[i] == '.'
		|| str[i] == ':' || str[i] == '/' || str[i] == '{' || str[i] == '}' || str[i] == '+'
		|| str[i] == '^' || str[i] == '%' || str[i] == '#' || str[i] == '@' || str[i] == '!'
		|| str[i] == '~'
		|| (str[i] == '=' && i == 0) || str[i] == '-' || str[i] == '?' || str[i] == '&' || str[i] == '*')
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

int	ft_export(t_cmds *cmd, t_shell *shell, char *str)
{
	int		i;
	int		check;
	int		identifier;

	i = 1;
	if (!str && !cmd->str[1])
	{
		sort_env(shell);
		print_env(shell->sorted_env);
		return (1);
	}
	if (str)
		send_arr(shell, str);
	else
	{
		while (cmd->str[i])
		{
			check = 0;
			identifier = check_identifier(cmd->str[i]);
			if (!str && !identifier)
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(cmd->str[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				check = 1;
			}
			else if (!str && !check_validity(cmd->str[i]))
				check = 1;
			else if (!str && if_exist(shell->env, cmd->str[i]))
				check = 1;
			else
			{
				if (!check)
				{
					if (identifier == 2)
						join_arr(shell, cmd->str[i]);
					else
						send_arr(shell, cmd->str[i]);
				}
			}
			i++;
		}
	}
	return (1);
}
