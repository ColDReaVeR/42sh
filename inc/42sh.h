/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 15:39:58 by hestela           #+#    #+#             */
/*   Updated: 2014/02/21 10:48:47 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __42SH_H__
# define __42SH_H__

# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>

typedef struct termios		t_term;
typedef struct dirent		t_dirent;
typedef struct winsize		t_win;
typedef struct stat			t_stat;

typedef struct				s_histo
{
	char					*line;
	struct s_histo			*next;
	struct s_histo          *prev;
	struct s_histo			*start;
}							t_histo;

typedef struct				s_pidlst
{
	int						num;
	pid_t					pid;
	char					*cmd;
	struct s_pidlst			*next;
	struct s_pidlst			*start;
}							t_pidlst;

typedef struct				s_alias_lst
{
	char					*alias;
	char					*string;
	struct s_alias_lst		*next;
	struct s_alias_lst		*start;
}							t_alias_lst;

typedef struct				s_env
{
	t_term					*term;
	char					**env;
	char					*cut;
	t_histo					*histo;
	char					**path;
	char					*in_exec;
	int						in_histo;
	int						quote_wait;
	pid_t					thread;
	t_pidlst				*pid_list;
	t_alias_lst				*alias_lst;
	char					**saved_line;
}							t_env;

typedef struct				s_cmd
{
	char					*line;
	int						redir;
	struct s_cmd			*next;
}							t_cmd;

typedef struct				s_quote
{
	char					c;
	struct s_quote			*next;
	struct s_quote			*prev;
}							t_quote;

typedef struct				s_comp_lst
{
	char					*str;
	struct s_comp_lst		*next;
	struct s_comp_lst		*start;
}							t_comp_lst;

extern char					**environ;
t_env						g_env;
t_win						g_ws;
int							g_prompt_len;
t_comp_lst					*g_comp_lst;

# define WRITE 1
# define READ 0

/*
** Colors
*/

# define PROMPT_CLR F_BLUE
# define TEXT_CLR F_CYAN
# define ERROR_CLR F_RED
# define INFOS_CLR F_GREEN

/*
** Keys
*/

# define TAB 900000
# define LEFT 279168000
# define RIGHT 279167000
# define UP 279165000
# define DOWN 279166000
# define BACK 12700000
# define CTRL_A 100000
# define CTRL_E 500000
# define END 279170000
# define HOME 279172000
# define CTRL_W 2300000
# define ALT_W -4351000
# define ALT_W2 -4311000
# define CTRL_X 2400000
# define CTRL_LEFT -23278872
# define CTRL_RIGHT -23278873
# define CTRL_D 400000
# define CTRL_C 300000
# define CTRL_Z 2600000
# define CTRL_UP -23278875
# define CTRL_DW -23278874

/*
** Read
*/

void		ft_get_input(char **line);
void		ft_check_position(void);
void		ft_check_key(char *buf, char **line, int *position, int *comp);
t_cmd		*ft_parser(char **line);
char		**ft_split_args(char *str);

/*
** Line édition
*/

void		ft_move_to_word_L(int *position, char **line);
void		ft_move_to_word_R(int *position, char **line);
void		ft_move_left(int *position, char *str);
void		ft_move_right(int *position, char *str);
void		ft_move_to_beg(int *position, char *str);
void		ft_move_to_end(int *position, char *str);
void		ft_move_up(int *position, char **line);
void		ft_move_down(int *position, char **line);
void		ft_del_char(char **line, int position);
void		ft_add_char(char **line, int position, char c);
void		ft_cut(char **line, int *position);
void		ft_copy(char **line, int position);
void		ft_paste(char **line, int *position);
void		ft_back(int *position, char **line);

/*
** Builtins
*/

int			ft_builtin(char **av);
void		ft_env(char **av, char **env);
int			ft_env_i(char **av);
void		ft_exec_without_env(char **av);
char		**ft_export(char **av, char **env);
char		**ft_setenv(char **av, char **env);
char		**ft_unsetenv(char **av, char **env);
void		ft_cd(char **av, char **env);
char		**ft_update_pwd(char *str, int mode);
void		ft_exit(char **av, int type);
int			ft_echo(char **av);
int			ft_put(int c);

/*
** Control jobs
*/

void		ft_suspend(int sig);
void		ft_add_to_pid_list(pid_t thread, char *cmd);
void		ft_del_pid_node(int id);
void		ft_got_pid_node(int id);
void		ft_got_node_nbr(void);
void		ft_print_job_list(void);
void		ft_resume(char **av);

/*
** Redirections
*/

void		ft_exec_pipe(char **av1, char**av2, char **env);
void		ft_exec_right(char **av1, char **av2, char **env);
void		ft_exec_right_d(char **av1, char **av2, char **env);
void		ft_exec_left(char **av1, char **av2, char **env);
void		ft_exec_left_d(char **av1, char **av2, char **env);
void		ft_get_heredoc(char **line);

/*
** History
*/

void		ft_update_history(char *line);
void		ft_previous_cmd(int *position, char **line);
void		ft_next_cmd(int *position, char **line);

/*
** Autocompletion
*/

void		ft_autocomp(char **line, int *position, int *autocomp);
char		*ft_autocomp_esc_space(char *str, t_stat file_stats);
void		ft_comp_file(char **ln, int *ps, int pv, int *comp);
void		ft_comp_file_3(char **ln, int pv, int *ps, char *path);
void		ft_comp_cmd(char **ln, int *ps, int pv, int *comp);
void		ft_comp_current_dir(char **ln, int *ps, int pv, int *comp);
void		ft_complete_all_cmd(char **line, int *ps, int pv, int *autocomp);
void		ft_add_comp_list(char *path, char *to_comp);
char		*ft_get_comp_path(char *begin);
char		*ft_get_comp_rest(char *begin);
void		ft_comp_path(char **ln, int pv, char *buf);
void		ft_rewrite_path(char **new, char *path);
void		ft_comp_refresh(char **line, char *buf, int *ps, int pv);

/*
** Replacement
*/

void		ft_do_replacements(char**line);
void		ft_replace_tilde(char **line);
void		ft_replace_variable(char **line);
void		ft_replace_alias(char **line);
void		ft_replace_star(char **line);
char		*ft_replace_star_2(char *path, char *stared, int *j, char *str);
void		ft_update_stared_line(char **line, char *new, int i);
void		ft_replace_script(char **line, int i, int j);
int			ft_check_is_cmd(char **line, char *buf, int i, int *j);
void		ft_in_string(char *quote, char c, int d);

/*
** Others
*/

void		ft_check_env(void);
void		ft_init(t_term *term);
void		ft_exec(char **av, char **env);
char		*ft_check_exist(char *cmd);
void		ft_resize(int sig);
void		ft_kill(int sig);
int			ft_check_quote(char **line);
void		ft_add_quote_to_list(t_quote **alist, char c);
int			ft_is_empty(char *s);
void		ft_env_changes(void);

#endif /* !__42SH_H__ */
