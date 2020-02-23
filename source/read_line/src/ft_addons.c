/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addons.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:09:38 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 18:12:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int			ft_countwords(char *str, int c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && str[i])
		{
			while (str[i] != c && str[i])
				i++;
			words++;
		}
		while (str[i] == c)
			i++;
	}
	return (words);
}

void		ft_nbrswap(int *a, int *b)
{
	int		c;

	c = *a;
	*a = *b;
	*b = c;
}

char		*get_base(char *path, int len)
{
	int i;

	i = len;
	while (--i >= 0)
		if (path[i] == '/')
			break ;
	return (ft_strsub(path, 0, i + 1));
}
