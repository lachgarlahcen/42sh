/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iv_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:17:49 by hastid            #+#    #+#             */
/*   Updated: 2020/01/19 02:06:36 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variable.h"

static t_var	*elem_var(char *value)
{
	t_var	*elem;

	if (!(elem = (t_var *)malloc(sizeof(t_var))))
		return (0);
	if (!(elem->value = ft_strdup(value)))
		return (0);
	elem->id = 1;
	elem->next = 0;
	return (elem);
}

static int		del_head(t_var **var)
{
	t_var	*tmp;

	tmp = *var;
	*var = (*var)->next;
	ft_memdel((void **)&tmp->value);
	ft_memdel((void **)&tmp);
	return (0);
}

int				ft_cmpvar(char *s1, char *s2)
{
	int		i;
	char	*tp1;
	char	*tp2;

	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	tp1 = ft_strsub(s1, 0, i);
	i = 0;
	while (s2[i] && s2[i] != '=')
		i++;
	tp2 = ft_strsub(s2, 0, i);
	if (!ft_strcmp(tp1, tp2))
		i = 0;
	ft_memdel((void **)&tp1);
	ft_memdel((void **)&tp2);
	if (i)
		return (1);
	return (0);
}

int				add_to_var(t_var **var, char *value)
{
	t_var	*tmp;

	if (*var)
	{
		tmp = *var;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = elem_var(value)))
			return (1);
	}
	else if (!(*var = elem_var(value)))
		return (1);
	return (0);
}

int				add_elem(t_var **var, char *value)
{
	t_var	*tmp;

	tmp = *var;

	while (tmp && ft_cmpvar(value, tmp->value))
		tmp = tmp->next;
	if (tmp)
	{
		ft_memdel((void **)&tmp->value);
		if (!(tmp->value = ft_strdup(value)))
			return (1);
	}
	else if (add_to_var(var, value))
		return (1);
	return (0);
}

int				del_elem(t_var **var, char *value)
{
	t_var	*tmp;
	t_var	*prev;

	if (*var && !ft_cmpvar(value, (*var)->value))
		return (del_head(var));
	tmp = *var;
	while (tmp && ft_cmpvar(value, tmp->value))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prev->next = tmp->next;
		ft_memdel((void **)&tmp->value);
		ft_memdel((void **)&tmp);
	}
	return (0);
}
