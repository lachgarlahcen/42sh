/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:43:59 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/12 22:07:12 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*p;
	int		i;

	if (!s || !f)
		return (0);
	i = 0;
	if (!(p = (char *)malloc(ft_strlen(s) + 1)))
		return (0);
	while (s[i])
	{
		p[i] = f(s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
