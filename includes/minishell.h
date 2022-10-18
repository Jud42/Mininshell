/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/19 12:54:53 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h> //for mac
# include "../libft/libft.h"
//# include <linux/limits.h> //header for macro PATH_MAX

/*----token----*/
# define QUOTE 1
# define S_QUOTE 2
# define D_QUOTE 3
# define DOLLAR 4
# define REDIR_IN 5
# define HEREDOC 6
# define REDIR_OUT_S 7
# define REDIR_OUT_D 8
# define REDIR 9
/*--------MACRO-COLOR------------------*/
# define BOLDGREEN "\033[1m\033[36m"   
# define RESET "\033[m" //white color
/*-----------------------------------*/

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAIL -1

typedef struct s_ms
{
	char	**env_p;
	int		exit;
	pid_t	pid_sig;
}	t_ms;

extern t_ms	g_ms;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{	
	char			*cmd;
	char			**av;
	int				ac;
	int				fd_in;
	int				fd_out;
	int				fd_file;
	int				infile;
	int				outfile;
	int				exit;
	struct s_redir	*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_redir
{
	int				pos;
	int				sign;
	char			*name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_lst
{
	char			*line;
	char			**tab;
	int				nb_arg;
	int				heredoc;
	int				redirection;
	int				pipe;
	pid_t			*pid;
	int				**tube_fd;
	int				times;
	int				n_env;
	int				test;
	struct s_cmd	*head;
	struct s_env	*env;
	struct termios	saved;
}	t_lst;

/*---------- Builtins ----------*/
void		exec_builtin(t_cmd *node, t_lst *ms);
int			check_builtin(char *str);
int			parse_cmds(char *path, t_lst *ms);
static int	cd_home(void);
/*---------- CD ----------*/
char		*cd_only(t_lst *ms);
void		print_error(char *path);
int			ft_cd(char *path, t_lst *ms);

/*---------- ENV ----------*/
void		ft_env(t_lst *ms);

/*---------- Export ----------*/
int			ft_export(char *str, t_lst *ms);
static int	check_export(char *str, t_lst *ms);
void		sort_export(t_lst *ms);

/*---------- Unset ----------*/
void		ft_unset(char *str, t_lst *ms);

/*---------- PWD ----------*/
void		pwd(void);

/*---------- Echo ----------*/
void		ft_echo(char **cmd);

/*---------- Exit ----------*/
void		ft_exit(char **cmd, t_lst *li);
static	int	ft_str_isdigit(char *str);
void		ctl_d_exit(void);
/*--------- signals ---------*/
void		init_signals(void);
int			get_line(t_lst *term);
void		sig_handler(int signum);
void		child_signal(int flag);
void		daddy_signal(t_lst *li);
/*---------- Environment ----------*/
char		*get_env_value(char *env, t_lst *ms);
char		**env_2_str(t_lst *ms);
int			update_env(char **env, t_lst *ms);
void		new_env(char *str, t_lst *ms);
t_cmd		*init_minishell(char **env);
void		ft_error(char *func, char *str);
void		free_2ptr(char **str);

/*----------------------------------------------------------------------------*/
//JUD
	/*handle_input.c*/
void		msg_error(char *s1, char c, char *s2);
int			error_exist(char *s);
void		init_shell(t_lst *li, char **tab);
void		malloc_pid(t_lst **li);

	/*lexical_split.c && redirection.parse*/
int			redirection(char c);
int			count_redirection(char *s, int i);
int			count_sep(char *s, char sep);
void		write_redirection(char **p_word, char *s, int *i);
char		**lex_split(char *s, char sep);

	/*analyse_lexical.c*/
int			quote_exist(char *s);
int			redir_exist(char *s);
void		handle_action(t_lst **li);

	/*treat_quote_dollar.c*/
int			len_d_quote(char *s, t_lst *li);
char		*news_s_quote(char *s);
char		*news_d_quote(char *s, t_lst *li);
char		*handle_sign(char *s, int *i, t_lst *li);

	/*help_treat_quote_dollar.c*/
char		*take_val_var(char *s);

	/*list_utils.c*/
void		create_list(t_lst **li);
void		delete_first(t_lst **li);
void		delete_redir(t_redir *node);

	/*init_redirection.c && init_pipe*/
void		init_pipe(t_lst *li);
int			init_redir(t_cmd *node, t_lst *li);

	/*here_doc*/
int			here_doc(t_redir *red);	

	/*exec.c && exec_utils.c*/
void		dup_fd(int fd_in, int fd_out);
void		close_fd(t_cmd *node, t_lst **li);
void		take_path(char ***dest, char *cmd, t_lst *li);
void		exec_process(t_lst *li);
void		check_error(char *path);

	/*free_utils.c*/
void		free_all(t_lst *li);
void		free_list(t_lst *li);
void		free_env(t_env **env);
void		free_tab(char **tab);
void		free_pipe(t_lst *li);
void		print_list(t_lst *li);
/*----------------------------------------------------------*/
#endif
