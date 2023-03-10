/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:36:16 by aperin            #+#    #+#             */
/*   Updated: 2023/03/10 13:15:55 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NRM "\x1B[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT "\x1B[36mAlexis'Hell ~$ \x1B[0m"

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
	int				n;
	pid_t			pid;
	int				pipefd[2];
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_shell
{
	char	**env;
	char	**sorted_env;
	t_cmds	*cmds;
	int		return_value;
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
t_cmds	*new_cmd(int n);
void	list_to_tab(t_cmds *node, t_lexer *lexer);
void	free_cmds(t_cmds *cmds);

//Expander
t_lexer	*expand(t_lexer *lexer, t_shell *shell);
char	*single_quotes(char *exp_str, char *str, int *index);
char	*double_quotes(char *exp_str, char *str, int *index, t_shell *shell);
char	*get_var(char *str, int *index, t_shell *shell);

//Executor
void	execute(t_shell *shell);
bool	single_cmd(t_shell *shell);
int		execute_builtin(t_cmds *cmd, t_shell *shell);
void	ft_execve(t_cmds *cmd, t_shell *shell, char **path);
void	ft_waitpid(t_shell *shell);
bool	is_builtin(t_cmds *cmd);
int		ft_dup(int fd);
void	ft_dup2(int fd1, int fd2);
pid_t	ft_fork(void);
void	ft_pipe(int fd[2]);

//Redirections
bool	handle_redirections(t_cmds *cmd, t_shell *shell);
void	heredoc(t_lexer *heredoc, t_shell *shell);
void	expand_heredoc(char *str, int fd, t_shell *shell);

//Builtins
int		ft_pwd(void);
int		ft_echo(t_cmds *cmd);
int		ft_env(char **env);
int		ft_exit(t_cmds *cmd, int type);
int		ft_cd(t_cmds *cmd, t_shell *shell);
int		add_path(t_shell *shell, char *temp);
int		ft_export(t_cmds *cmd, t_shell *shell, char *str);
int		ft_unset(t_cmds *cmd, t_shell *shell);

//Builtins Utils
int		modify_path(t_shell *shell, char *temp, int code, int code2);
int		check_validity(char *str);
int		if_exist(char **env, char *str);
int		check_identifier(char *str);
int		is_identifier(char c);
char	*get_pwd(void);
void	print_env(char **env);
void	join_path(t_shell *shell, int i, char *temp, char *str);
int		check_identifier(char *str);
int		send_arr(t_shell *shell, char *str);
char	**new_arr(char **env, char **rtn, char *str);
void	join_arr(t_shell *shell, char *str);
int		if_exist(char **env, char *str);
void	check_and_send(t_shell *shell, char *str);

//Sort Env
void	sort_env(t_shell *shell);

//Utils
void	display_header(void);

//Handle Sig
void	ctrl_c(int sig);
void	sig_handler(void);

//Errors
int		export_err(char *str);
void	print_error(int error_code);

#endif
