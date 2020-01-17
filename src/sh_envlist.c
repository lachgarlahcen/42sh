/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_envlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 06:31:08 by hastid            #+#    #+#             */
/*   Updated: 2019/12/02 02:54:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static t_env	*elem_env(char *name, char *value)
{
	t_env	*elem;

	if (!(elem = (t_env *)malloc(sizeof(t_env))))
		return (0);
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

static int		del_head(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	*env = (*env)->next;
	ft_memdel((void **)&tmp->name);
	ft_memdel((void **)&tmp->value);
	ft_memdel((void **)&tmp);
	return (0);
}

int				add_to_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = elem_env(name, value)))
			return (1);
	}
	else if (!(*env = elem_env(name, value)))
		return (1);
	return (0);
}

int				add_elem(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
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
		else if (add_to_env(env, name, value))
			return (1);
	}
	else
		ft_putenv(tmp);
	return (0);
}

int				del_elem(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	if (*env && !ft_strcmp(name, (*env)->name))
		return (del_head(env));
	tmp = *env;
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
