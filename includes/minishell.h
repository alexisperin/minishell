/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:36:16 by aperin            #+#    #+#             */
/*   Updated: 2023/02/14 13:01:56 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include <readline/readline.h>
# include <readline/history.h>

# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef enum e_token
{
	P = 1,
	L,
	LL,
	R,
	RR
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_cmds
{
	char			**str;
	t_lexer			*redir;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_shell
{
	char	**env;
	t_cmds	*cmds;
}			t_shell;

//Read input
void	read_input(t_shell *shell);

//Lexer
t_lexer	*get_lexer(char *line);
bool	prelexer_check(char *str);
bool	postlexer_check(t_lexer *lexer);
size_t	next_quote(char *str, size_t start);
size_t	skip_spaces(char *line);
t_token	get_token(char *str);
void	lexer_add_back(t_lexer **lexer, t_lexer *node);
void	free_lexer(t_lexer *lexer);

//Parser
t_cmds	*get_cmds(t_lexer *lexer);
void	list_to_tab(t_cmds *node, t_lexer *lexer);
void	free_cmds(t_cmds *cmds);

//Expander
void	expander(t_cmds *cmd, char **env);
int		get_expanded_size(char *str, char **env);
int		key_len(char *str);
int		var_len(char *str, int len, char **env);

//Executor
void	execute(t_shell *shell);

//Builtins
int	ft_pwd(void);
int	ft_echo(t_cmds *cmd);
int	ft_env(t_cmds *cmd, char **env);

//Utils
void	display_header(void);

//Errors
void	print_error(int error_code);

#endif
