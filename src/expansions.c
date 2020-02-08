/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:47:46 by aihya             #+#    #+#             */
/*   Updated: 2020/02/08 22:20:39 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*expand(char *exp, int *status)
{
	char	**args;
	char	*p;
	char	*clean_exp;
	size_t	counter;

	*status = 0;
	if (exp[0] != '{')
		return (get_variable(exp));
	clean_exp = uncover_exp(exp);
	if (clean_exp[0] == '#')
		return (length_expansion(clean_exp + 1, status));
	if (clean_exp != NULL)
	{
		counter = ft_char_count(clean_exp, ':');
		if (counter == 0)
			return (unary_expansion(clean_exp, status));
		else if (counter == 1)
			return (binary_expansion(clean_exp, status));
	}
	*status = 1;
	return (NULL);
}

char	*uncover_exp(char *exp)
{
	char	*uncovered;
	char	**array;

	uncovered = NULL;
	array = ft_strsplit_del(exp, "{}");
	if (ft_chain_size(array) == 0)
	{
		ft_chain_free(&array);
		return (NULL);
	}
	uncovered = ft_strdup(array[0]);
	ft_chain_free(&array);
	return (uncovered);
}

char	*lenght_expansion(char *exp, int *status)
{
	int		i;
	char	*value;
	char	*expansion;

	*status = 0;
	if (exp[0] == '#')
		return (ft_strdup("0"));
	i = 0;
	while (exp[i])
	{
		if ((i == 0 && ft_isdigit(exp[i]))
		|| (!ft_isalphanumeric(exp[i]) && (exp[i] != '_')))
		{
			*status = BAD_SUBSTITUTION;
			return (NULL);
		}
		i++;
	}
	value = get_variable(exp);
	expansion = ft_itoa_base(ft_strlen(value), 10);
	return (expansion);
}

char	*unary_expansion(char *exp, int *status)
{
	if (exp[0] == '#' && exp[1] && exp[1] != '#')
		return (lenght_expansion(exp + 1, status));
	
}