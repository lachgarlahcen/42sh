/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_fc_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 04:19:31 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:44:12 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#define FC_TMP_FILE "/tmp/fc-42sh.tmp"

static int ft_fc_write_to_file(t_hist *h, t_fc *fc, int f, int l)
{
    int i;
    int fd;

    if (!(fd = open(FC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC,
                    S_IRUSR | S_IWUSR)))
    {
        ft_putendl_fd(2, "42sh: fc: cannot open temp file");
        return (0);
    }
    if (fc->r)
    {
        i = f;
        f = l;
        l = i;
    }
    i = 0;
    while (f <= l)
    {
        ft_putendl_fd(get_element_by_index(h->hist_list, f), fd);
        i = 1;
        f++;
    }
    while (!i && f >= l)
    {
        ft_putendl_fd(get_element_by_index(h->hist_list, f), fd);
        f--;
    }
    close(fd);
    return (1);
}

void ft_fc_lanch_editor(t_fc *fc)
{
    char *editor;

    editor = ft_strjoin_f(ft_strjoin(fc->editor, " "), FC_TMP_FILE, 1, 0);
    // execute the editor in pipline

    free(editor);
}

int ft_fc_execute_file(t_fc *fc)
{
    int fd;
    char *line;

    if (!(fd = open(FC_TMP_FILE, O_RDONLY)))
    {
        ft_putendl_fd(2, "42sh: fc: cannot open temp file");
        return (0);
    }
    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        // execute the cm in pipline

        ft_strdel(&line);
    }
    close(fd);
    return (1);
}

int ft_fc_editor(t_fc *fc)
{
    int f;
    int l;
    t_hist *hist;

    !fc->editor ? fc->editor = "ed" : 1 == 1;
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
    f = f < 0 ? ABS(f) : (hist->count - f - 1);
    l = l < 0 ? ABS(l) : (hist->count - l - 1);
    if (!ft_fc_write_to_file(hist, fc, f, l))
        return (0);
    ft_fc_lanch_editor(fc);
    if (!ft_fc_execute_file(fc))
        return (0);
    return (1);
}