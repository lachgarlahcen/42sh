/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 00:59:17 by hastid            #+#    #+#             */
/*   Updated: 2020/02/05 03:11:29 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "intern_variables.h"

t_var	*get_intern_variables(t_var **v, int check)
{
	static t_var	*st_var;

	if (check)
		st_var = *v;
	return (st_var);
}

void	init_variables(char **env)
{
	t_var	*v;

	v = 0;
	if (env)
		v = creat_variables(env);
	get_intern_variables(&v, 1);
}

void	free_variables(void)
{
	t_var	*var;
	t_var	*tmp;

	var = get_intern_variables(0, 0);
	while (var)
	{
		tmp = var->next;
		ft_memdel((void **)&(var->name));
		ft_memdel((void **)&(var->value));
		ft_memdel((void **)&var);
		var = tmp;
	}
	var = get_intern_variables(&var, 1);
}
