/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:10:14 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/17 19:14:23 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strctrim(char const *s, char c)
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
	while ((s[i] == c && i > 0))
		i--;
	e = i;
	p = ft_strsub(s, b, ((e >= b) ? (e - b) : (b - e)) + 1);
	return (p);
}
