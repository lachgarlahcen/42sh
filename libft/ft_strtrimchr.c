/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:08:49 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/16 23:29:02 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimchr(char const *s, char c)
{
	int		i;
	int		b;
	int		e;
	char	*p;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == c)
		i++;
	b = i;
	while (s[i])
		i++;
	i--;
	while ((s[i] == c) && i > 0)
		i--;
	e = i;
	p = ft_strsub(s, b, ((e >= b) ? (e - b) : (b - e)) + 1);
	if (!p)
		return (0);
	return (p);
}
