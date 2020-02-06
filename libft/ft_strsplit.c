/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 15:38:15 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/16 23:30:12 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	mycalc(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			j++;
			while (s[i] && s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (j + 2);
}

static char	**ft_finall(char const *s, char c)
{
	unsigned int	i;
	int				k;
	int				start;
	char			**p;

	p = (char **)malloc(mycalc((char *)s, c) * sizeof(char *));
	start = 0;
	i = 0;
	k = 0;
	while (i++ <= ft_strlen(s))
	{
		if (s[i] == c || s[i] == '\0')
		{
			p[k++] = ft_strsub(s, start, i - start);
			if (s[i++])
				while (s[i] && s[i] == c)
					i++;
			start = i;
		}
	}
	p[k] = 0;
	return (p);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**p;

	p = 0;
	if (!s)
		return (0);
	s = ft_strtrimchr(s, c);
	if (!s)
		return (0);
	p = ft_finall(s, c);
	free((void *)s);
	return (p);
}
