/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:08:36 by hastid            #+#    #+#             */
/*   Updated: 2019/12/22 13:20:52 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SHELL_H
# define MY_SHELL_H

# include "../libft/libft.h"
# include "../line_editing/line_editing.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

# define READ_SIZE 1000000

typedef struct	s_tok
{
	int				id;
	char			*value;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_line
{
	int		rd;
	char	**args;
}				t_line;

typedef struct	s_pipe
{
	t_tok			*tok;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_file
{
	int	in;
	int	out;
	int	err;
}				t_file;

char			*aff_prompt(t_env *env);
int				split_pipe(char *tmp, t_env **env);
int				split_lines(char *line, t_env **env);
char			*sub_line(char **tmp, char *line, char c);
int				analy_toks(t_tok *toks);
int				check_error(t_tok *toks);
int				check_save(t_tok **toks, char *line);
t_tok			*split_tokens(char *line);
char			*sub_token(char **tmp, char *line);
int				cmd_line(char *line, t_env **env);

int				check_space(char c);
int				check_spechar(char c);
int				check_pipe(char *str);
int				check_token(char *token);
int				check_errline(char *str);
int				check_number(char *token, int check);
int				check_error_red(t_tok *prev, t_tok *toks);

void			free_tab(char **tab);
void			free_pipes(t_pipe *pip);
void			free_tokens(t_tok *lst);
void			free_file(t_file *file);
void			free_environ(t_env *lst);
int				save_tokens(t_tok **tok, char *token, int id);

char			*add_to_file(char *file, char *s);
int				save_file(t_file **file, int in, int out, int err);

int				check_built(char *str);

void			ft_putenv(t_env *env);
int				ft_setenv(t_env **env, char **args);
int				ft_unsetenv(t_env **env, char **args);
int				add_elem(t_env **env, char *name, char *value);
int				add_to_env(t_env **env, char *name, char *value);
int				del_elem(t_env **env, char *name);
t_env			*creat_env(char **env);
char			**list_to_tab(t_env *env);

int				built_cd(char **args, t_env **env);
char			*ft_getenv(t_env *env, char *name);

int				isdir(char *path);
char			*path_of_link(char *dir, char *pwd);

int				ft_perror(char *s, char *str, int ret);
char			*parse_line(char *tmp, t_env *env);
char			*excutable(char *str, t_env *env);
int				execute_pipe(int inp, int pi[2], t_env **env, t_pipe *pipes);

char			*prompt(t_env *env);
int				edit_etoile(t_tok **toks, char *str, int id);
char			*ft_strjoin_f(char *s1, char *s2, int a, int b);
int				duplicate(t_tok *toks);
int				execute_tok(t_tok *t, t_env **env);
int				execute(t_tok *t, t_env **env);
int				execute_builtins(t_tok *t, t_env **env);
char			**args_execve(t_tok *t);
char			*search_executable(char *exe, t_env *env);
int				duplicate_file(char *fd, int rd, char *file, int n_id);
int				search_exit(t_tok *t);
int				end_quotes(char *str, int be, char q);
int				heredirect(char *file);

#endif
