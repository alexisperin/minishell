/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:36:16 by aperin            #+#    #+#             */
/*   Updated: 2023/02/02 09:24:51 by aperin           ###   ########.fr       */
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
#  define PATH_MAX 250
# endif

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
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_cmds
{
	char			**str;
	int				size;
	t_lexer			*redir;
	struct s_cmds	*next;
}					t_cmds;

void	print_lexer(t_lexer *lexer); // TO REMOVE

//Read input
void	read_input(void);

//Lexer
t_lexer	*get_lexer(char *line);
bool	prelexer_check(char *str);
bool	postlexer_check(t_lexer *lexer);
size_t	skip_spaces(char *line);
t_token	get_token(char *str);
void	lexer_add_back(t_lexer **lexer, t_lexer *node);
void	free_lexer(t_lexer *lexer);

//Parser
t_cmds	*get_cmds(t_lexer *lexer);
char	**list_to_tab(t_cmds *node, t_lexer *lexer);

//Builtins
void	ft_pwd(void);

//Utils
void	display_header(void);

//Errors
void	print_error(int error_code);

#endif
