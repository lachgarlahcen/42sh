/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:46:01 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/14 20:58:41 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../src/my_shell.h"
# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>
# include <unistd.h>
# include <limits.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

# define BUFF_SIZE 1000000
# define LEFT_K 4479771
# define TOP_K 4283163
# define RIGHT_K 4414235
# define BOTTOM_K 4348699
# define UP_K 2117425947
# define DOWN_K 2117491483
# define SPACE_K 32
# define DEL_K 2117294875
# define BACK_K 127
# define ESC_K 27
# define TAB_K 9
# define DELALL_K 42
# define REV_K 5921563
# define HOME_K 4741915
# define END_K 4610843
# define INTER_K 10
# define ALT_L_K 1146821403
# define ALT_R_K 1130044187
# define ALT_U_K 1096489755
# define ALT_D_K 1113266971
# define ALT_X_K 8948194
# define CTL_F 6
# define CTL_D 4
# define CTL_B 2
# define CTL_L 12
# define ALT_A 42435
# define COLS (tgetnum("co"))
# define ROWS (tgetnum("li"))
# define SO (tgetstr("so", NULL))
# define SE (tgetstr("se", NULL))
# define CL (tgetstr("cl", NULL))
# define CM (tgetstr("cm", NULL))
# define VE (tgetstr("ve", NULL))
# define VI (tgetstr("vi", NULL))
# define US (tgetstr("us", NULL))
# define TE (tgetstr("te", NULL))
# define TI (tgetstr("ti", NULL))
# define CE (tgetstr("ce", NULL))
# define CR (tgetstr("cr", NULL))
# define LE (tgetstr("le", NULL))
# define ND (tgetstr("nd", NULL))
# define CD (tgetstr("cd", NULL))
# define CH (tgetstr("ch", NULL))
# define SC (tgetstr("sc", NULL))
# define RC (tgetstr("rc", NULL))
# define AL (tgetstr("AL", NULL))
# define DO (tgetstr("do", NULL))
# define NORM (tgetstr("me", NULL))
# define MSG1 (ft_putstr_fd("Error occured\n", 2))
# define MSG2 (ft_putstr_fd("Not enough room.\n", 2))
# define MSG3 (ft_putstr_fd("No arguments received.\n", 2))
# define ERROR_EXIT {MSG1;exit(0);}
# define WRONG_SIZE ({MSG2;return;})
# define NO_ARG {MSG3;exit(0);}
# define DB_Q(a, b) (a == '\'' && (b % 2) == 0)
# define S_Q(a, b) (a == '\"' && (b % 2) == 0)
# define S_S(a) ((a == ' ' || a == '\t'))
# define GREEN "\e[0;92m"
# define BLUE "\e[0;34m"
# define YELLO "\e[0;93m"
# define RED "\e[0;91m"
# define WHITE "\e[0;97m"
# define RESET "\e[39m"
# define HISTORY_FILE_PATH "/tmp/.21sh_history"
# define O_FILL (O_CREAT | O_WRONLY | O_TRUNC)

typedef struct		s_cmd
{
	int				cur;
	int				len;
	int				key;
	int				b_p;
	int				is_s;
	int				s_sp;
	int				res;
	int				h_p;
	int				ctl_d;
	int				ctl_c;
	struct winsize	w;
	struct s_point	*init_p;
	struct s_point	*cur_p;
	struct s_hist	*hist;
	char			chars[BUFF_SIZE];
	char			cpy[BUFF_SIZE];
	char			prompt[PATH_MAX];
}					t_cmd;
typedef struct		s_key
{
	long			key;
	void			(*f)(t_cmd *l);
}					t_key;
typedef struct		s_point
{
	int				r;
	int				c;
}					t_point;

typedef struct		s_data
{
	char			*data;
	struct s_data	*next;
}					t_data;

typedef	struct		s_hist
{
	struct s_data	*hist_list;
	char			*tmp;
	int				count;
	int				col;
}					t_hist;

typedef	struct		s_tab
{
	char			*cmd;
	struct s_tab	*next;
}					t_tab;

void				right_key(t_cmd *l);
void				left_key(t_cmd *l);
void				alt_r_k(t_cmd *l);
void				esc_key(t_cmd *l);
void				delete(t_cmd *l);
void				home_k(t_cmd *l);
void				end_k(t_cmd *l);
void				sheft(t_cmd *l);
void				up_k(t_cmd *l);
void				down_k(t_cmd *l);
void				top_k(t_cmd *l);
void				add_at(t_cmd *l);
void				alt_l_k(t_cmd *l);
void				alt_u_k(t_cmd *l);
void				alt_d_k(t_cmd *l);
void				ctl_left(t_cmd *l);
void				return_k(t_cmd *l);
void				bottom_k(t_cmd *l);
void				ctl_right(t_cmd *l);
void				alt_x_k(t_cmd *l);
void				ctl_d(t_cmd *l);
void				ctl_l(t_cmd *l);
void				init_term(void);
t_cmd				*init_cmd(char *prompt);
char				*read_line(char *prompt);
void				plus(t_point *p, t_cmd *l, t_point *p1, int i);
void				mines(t_point *p, t_cmd *l);
void				get_cur_pos(t_point *t);
void				init_history();
void				add_to_hist(char *cmd);
void				default_term_mode(void);
int					f_l(int a, int b, int first);
int					change_spaces(char *str);
t_hist				*save_hist(t_hist **hist);
t_cmd				*keep_l(t_cmd *l, int cmd);
void				free_out(t_cmd *l);
void				print_cmd(t_cmd *l);
void				go_to_the_end(t_cmd *l);
void				free_history(void);
void				swap_p(t_point	*p1, t_point	*p2, int a);
void				excute_key(t_key	keys[18], t_cmd *l);
void				win_ch(int seg);
void				show_prompt(t_cmd *l);
void				alt_a(t_cmd *l);
int					get_next_line(const int fd, char **line);
void				write_backword(int fd, t_data *list);
void				init_cur(t_cmd *l);
#endif
