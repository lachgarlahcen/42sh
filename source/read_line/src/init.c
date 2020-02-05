/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:33:26 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:44:34 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static t_cmd *malloc_cmd(void)
{
	t_cmd *l;

	l = (t_cmd *)malloc(sizeof(t_cmd));
	l->init_p = (t_point *)malloc(sizeof(t_point));
	l->cur_p = (t_point *)malloc(sizeof(t_point));
	return (l);
}

void swap_p(t_point *p1, t_point *p2, int a)
{
	if (a)
	{
		p1->c = p2->c;
		p1->r = p2->r;
	}
	else
	{
		p2->c = p1->c;
		p2->r = p1->r;
	}
}

t_cmd *init_cmd(char *pr)
{
	t_cmd *l;

	l = malloc_cmd();
	if (l == NULL || l->init_p == NULL || l->cur_p == NULL)
		return (NULL);
	ft_strcpy(l->prompt, pr);
	get_cur_pos(l->cur_p);
	get_cur_pos(l->init_p);
	show_prompt(l);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
	l->len = 0;
	l->b_p = 0;
	l->cur_p->c--;
	l->cur_p->r--;
	l->cur = 0;
	l->hist = NULL;
	l->cpy[0] = 0;
	l->is_s = 0;
	l->s_sp = 0;
	l->res = 1337;
	l->h_p = -1;
	l->ctl_d = 0;
	l->ctl_c = 0;
	return (l);
}

void init_term(void)
{
	char *termtype;
	int success;
	struct termios tattr;

	termtype = getenv("TERM");
	if (termtype == 0)
		ft_putstr_fd("Specify a terminal type'.\n", 2);
	success = tgetent(0, termtype);
	if (success < 0)
		ft_putstr_fd("Could not access the termcap data base.\n", 2);
	if (success == 0)
		ft_putstr_fd("Terminal type  is not defined.\n", 2);
	if (termtype == 0 || success <= 0)
		exit(0);
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}
