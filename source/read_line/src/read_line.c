/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:13:47 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:55:42 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void default_term_mode(void)
{
	struct termios tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

void read_key(t_cmd *l)
{
	int res;
	char buff[READ_SIZE];
	int i;

	res = read(0, buff, READ_SIZE);
	ft_bzero(buff + res, 3);
	i = -1;
	while (buff[++i] && ft_isprint(buff[i]))
	{
		l->key = buff[i];
		add_at(l);
	}
	l->key = 0;
	if (res <= 4)
		l->key = *(int *)buff;
}

void print_cmd(t_cmd *l)
{
	t_point p;
	int i;

	i = -1;
	init_cur(l);
	ft_putstr_fd(tgoto(CM, l->init_p->c - 1, l->init_p->r - 1), 1);
	ft_putstr_fd(CD, 1);
	show_prompt(l);
	while (++i < l->len)
	{
		if (i == l->cur)
			swap_p(&p, l->cur_p, 1);
		if (i == (l->cur - l->s_sp) && l->is_s)
			ft_putstr_fd(SO, 1);
		if (i == l->cur && l->is_s)
			ft_putstr_fd(SE, 1);
		if (l->chars[i] != '\n')
			ft_putchar_fd(l->chars[i], 1);
		plus(l->cur_p, l, &p, i);
	}
	if (l->cur != l->len)
		swap_p(&p, l->cur_p, 0);
	ft_putstr_fd(tgoto(CM, l->cur_p->c, l->cur_p->r), 1);
	ft_putstr_fd(SE, 1);
}

void match_key(t_cmd *l)
{
	static t_key keys[TOUCH_COUNT] = {
		{RIGHT_K, &right_key},
		{LEFT_K, &left_key},
		{BACK_K, &delete},
		{END_K, &end_k},
		{HOME_K, &home_k},
		{INTER_K, &return_k},
		{CTL_D, &ctl_d},
		{CTL_B, &ctl_left},
		{CTL_F, &ctl_right},
		{UP_K, &up_k},
		{DOWN_K, &down_k},
		{ALT_L_K, &alt_l_k},
		{ALT_U_K, &alt_u_k},
		{ALT_D_K, &alt_d_k},
		{ALT_X_K, &alt_x_k},
		{TOP_K, &top_k},
		{BOTTOM_K, &bottom_k},
		{CTL_L, &ctl_l},
		{ALT_A, &alt_a},
		{TAB_K, &completion},
		{CTL_R, &show_history},
	};

	excute_key(keys, l);
}

char *read_line(char *prompt)
{
	t_cmd *l;
	char *result;

	init_term();
	if ((l = init_cmd(prompt)) == NULL)
		return (0);
	l->chars[0] = 0;
	keep_l(l, 0);
	while (l->res)
	{
		read_key(l);
		match_key(l);
		print_cmd(l);
		if (l->is_s == 0)
			l->s_sp = 0;
		l->is_s = 0;
	}
	go_to_the_end(l);
	default_term_mode();
	if (l->ctl_d)
		result = NULL;
	else
		result = ft_strdup(l->ctl_c ? "\0" : l->chars);
	free_out(l);
	return (result);
}
