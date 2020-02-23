/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_fc_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 04:19:31 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 00:13:25 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#define FC_TMP_FILE "/tmp/fc-42sh.tmp"

void			ft_nbrswap(int *a, int *b)
{
	int		c;

	c = *a;
	*a = *b;
	*b = c;
}

static int		ft_fc_write_to_file(t_hist *h, t_fc *fc, int f, int l)
{
	int i;
	int fd;

	if (!(fd = open(FC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR)))
	{
		ft_putendl_fd("42sh: fc: cannot open temp file", 2);
		return (0);
	}
	if (fc->r)
		ft_nbrswap(&f, &l);
	i = 0;
	while (f <= l)
	{
		ft_putendl_fd(get_element_by_index(f, h->hist_list), fd);
		i = 1;
		f++;
	}
	while (!i && f >= l)
	{
		ft_putendl_fd(get_element_by_index(f, h->hist_list), fd);
		f--;
	}
	close(fd);
	return (1);
}

void			ft_fc_lanch_editor(t_fc *fc)
{
	char *editor;

	editor = ft_strjoin_f(ft_strjoin(fc->editor, " "), FC_TMP_FILE, 1, 0);
	g_h = 0;
	line_editing(editor, 0);
	ft_strdel(&editor);
}

int				ft_fc_execute_file(t_fc *fc)
{
	int		fd;
	char	*line;

	(void)fc;
	if (!(fd = open(FC_TMP_FILE, O_RDONLY)))
	{
		g_h = 0;
		ft_putendl_fd("42sh: fc: cannot open temp file", 2);
		return (0);
	}
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			ft_putendl_fd(line, 2);
			line_editing(line, 0);
		}
		ft_strdel(&line);
		line = NULL;
	}
	close(fd);
	g_h = 0;
	return (1);
}

int				get_real_index(int v, int count)
{
	if (v > 0)
		return (count - v);
	else if (v < 0)
		return (ABS(v) - 1);
	return (v);
}

int				ft_fc_editor(t_fc *fc)
{
	int		f;
	int		l;
	t_hist	*hist;

	fc->editor = !fc->editor ? ft_strdup("ed") : fc->editor;
	f = 0;
	l = 0;
	if (fc->first)
		if (!ft_fc_get_pos(fc->first, &f) || !ft_fc_get_pos(fc->last, &l))
		{
			ft_putstr_fd("42sh: fc: history specification out of range\n", 2);
			return (0);
		}
	hist = NULL;
	hist = save_hist(&hist);
	hist->count < ABS(f) ? f = 0 : 1 == 1;
	hist->count < ABS(l) ? l = 0 : 1 == 1;
	f = get_real_index(f, hist->count);
	l = get_real_index(l, hist->count);
	if (!ft_fc_write_to_file(hist, fc, f, l))
		return (0);
	ft_fc_lanch_editor(fc);
	if (!ft_fc_execute_file(fc))
		return (0);
	return (1);
}
