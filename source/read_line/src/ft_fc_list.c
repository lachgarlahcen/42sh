/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 22:26:33 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:44:19 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#define ABS(x) ((x) < 0 ? -(x) : (x))

int ft_fc_get_pos(char *arg, int *pos)
{
    int index;

    if (!arg || arg[0] == '0')
    {
        *pos = 0;
        return (1);
    }
    index = ft_atoi(arg);
    if (index)
    {
        *pos = index;
        return (1);
    }
    index = get_history_pos_by_match(arg);
    if (index != -1)
    {
        *pos = index;
        return (1);
    }
    return (0);
}

static void ft_fc_print_list(t_hist *h, t_fc *fc, int f, int l)
{
    int i;

    if (fc->r)
    {
        i = f;
        f = l;
        l = i;
    }
    i = 0;
    while (f <= l)
    {
        fc->n ? ft_printf("%4d", h->count - f) : 1 == 1;
        ft_putendl_fd(get_element_by_index(h->hist_list, f), 1);
        i = 1;
        f++;
    }
    while (!i && f >= l)
    {
        fc->n ? ft_printf("%4d", h->count - f) : 1 == 1;
        ft_putendl_fd(get_element_by_index(h->hist_list, f), 1);
        f--;
    }
}

void ft_fc_list_history(t_fc *fc, int f, int l)
{
    t_hist *hist;

    hist = NULL;
    hist = save_hist(&hist);
    hist->count < ABS(f) ? f = 0 : 1 == 1;
    hist->count < ABS(l) ? l = 0 : 1 == 1;
    f = f < 0 ? ABS(f) : (hist->count - f - 1);
    l = l < 0 ? ABS(l) : (hist->count - l - 1);
    ft_fc_print_list(hist, fc, f, l);
}

int ft_fc_list(t_fc *fc)
{
    int f;
    int l;

    f = -16;
    l = 0;
    if (fc->first)
        if (!ft_fc_get_pos(fc->first, &f) || !ft_fc_get_pos(fc->last, &l))
        {
            ft_putstr_fd("42sh: fc: history specification out of range\n", 2);
            return (0);
        }
    ft_fc_list_history(fc, f, l);
    return (1);
}