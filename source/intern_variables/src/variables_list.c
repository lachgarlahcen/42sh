/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:00:49 by hastid            #+#    #+#             */
/*   Updated: 2020/02/24 23:11:45 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

static t_var	*elem_var(char *name, char *value, int id)
{
	t_var	*elem;

	if (!(elem = (t_var *)malloc(sizeof(t_var))))
		return (0);
	elem->id = id;
	if (!(elem->name = ft_strdup(name)))
		return (0);
	if (value)
		if (!(elem->value = ft_strdup(value)))
			return (0);
	if (!value)
		if (!(elem->value = ft_strdup("\0")))
			return (0);
	elem->next = 0;
	return (elem);
}

static int		del_head(t_var **var)
{
	t_var	*tmp;

	tmp = *var;
	*var = (*var)->next;
	ft_memdel((void **)&tmp->name);
	ft_memdel((void **)&tmp->value);
	ft_memdel((void **)&tmp);
	return (0);
}

int				add_to_var(t_var **var, char *name, char *value, int id)
{
	t_var	*tmp;

	if (*var)
	{
		tmp = *var;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = elem_var(name, value, id)))
			return (1);
	}
	else if (!(*var = elem_var(name, value, id)))
		return (1);
	return (0);
}

int				add_elem(t_var **var, char *name, char *value, int id)
{
	t_var	*tmp;

	tmp = *var;
	if (name)
	{
		while (tmp && ft_strcmp(name, tmp->name))
			tmp = tmp->next;
		if (tmp)
		{
			ft_memdel((void **)&tmp->value);
			if (value)
			{
				if (!(tmp->value = ft_strdup(value)))
					return (1);
			}
			else if (!(tmp->value = ft_strdup("\0")))
				return (1);
		}
		else if (add_to_var(var, name, value, id))
			return (1);
	}
	return (0);
}

int				del_elem(t_var **var, char *name)
{
	t_var	*tmp;
	t_var	*prev;

	if (*var && !ft_strcmp(name, (*var)->name))
		return (del_head(var));
	tmp = *var;
	while (tmp && ft_strcmp(name, tmp->name))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prev->next = tmp->next;
		ft_memdel((void **)&tmp->name);
		ft_memdel((void **)&tmp->value);
		ft_memdel((void **)&tmp);
	}
	return (0);
}
