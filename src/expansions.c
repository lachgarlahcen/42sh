/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:47:46 by aihya             #+#    #+#             */
/*   Updated: 2020/02/13 10:08:34 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

typedef struct	s_expansion
{
	char	*front;		// ?, #
	char	*parameter;
	char	*middle;	// :, +, -, ?, =
	char	*rest;		
}				t_expansion;

char		*read_front(char *exp, int *index)
{
	char	*front;

	front = NULL;
	while (exp[*index])
	{
		if (ft_strchr('?#', exp[*index]))
		{
			ft_strappend(&front, exp[*index], TRUE);
			(*index)++;
		}
		break ;
	}
	return (front);
}

char		*read_parameter(char *exp, int *index)
{
	char	*parameter;

	parameter = NULL;
	while (exp[*index])
	{
		if (ft_isalphanumeric(exp[*index]) || (exp[*index] == '_'))
		{
			ft_strappend(&parameter, exp[*index], TRUE);
			(*index)++;
		}
		break ;
	}
	return (parameter);
}



t_expansion	*parse_expansion_format(char *exp)
{
	int		index;
	t_expansion	*expansion;

	expansion = (t_expansion *)malloc(sizeof(t_expansion));
	if (expansion == NULL)
		return (NULL);
	index = 0;
	expansion->front = read_front(exp, &index);
	expansion->parameter = read_parameter(exp, &index);
	expansion->middle = read_middle(exp, &index);
	expansion->rest = read_rest(exp, &index);
	return (expansion);
}

