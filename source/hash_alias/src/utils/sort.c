/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:29:19 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:22:32 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	swap(char **s1_p, char **s2_p)
{
	char	*s;

	s = *s1_p;
	*s1_p = *s2_p;
	*s2_p = s;
}

void	sort(char **chain, size_t size)
{
	size_t	i;
	size_t	j;

	if (size != 0)
	{
		i = 0;
		while (i < size - 1)
		{
			j = i + 1;
			while (j < size)
			{
				if (ft_strcmp(chain[i], chain[j]) > 0)
					swap(&chain[i], &chain[j]);
				j++;
			}
			i++;
		}
	}
}
