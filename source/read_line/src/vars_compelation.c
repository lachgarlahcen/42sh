/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_compelation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:45:43 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 18:09:03 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int		fill_vars(char *match, t_data **matches, int opt)
{
	int		res;
	t_data	*new_match;
	t_var	*var;
	char	*tmp;

	res = 0;
	var = get_intern_variables(NULL, 0);
	if (!var)
		return (0);
	while (var)
	{
		if (!ft_memcmp(match, var->name, ft_strlen(match)))
		{
			tmp = opt ? ft_strjoin_f(var->name, "}", 0, 0) :
				ft_strdup(var->name);
			new_match = new_node(tmp);
			sortedisert(matches, new_match);
			res++;
		}
		var = var->next;
	}
	return (res);
}

void	vars_compelation(char *match, t_cmd *l)
{
	int		i;
	int		opt;
	int		count;
	t_data	*matches;

	i = 0;
	opt = 0;
	matches = NULL;
	if (ft_strlen(match) >= 2 && match[1] == '{')
		opt = 1;
	count = fill_vars(opt ? &match[2] : &match[1], &matches, opt);
	complete_or_print(matches, l, count, opt ? &match[2] : &match[1]);
}
