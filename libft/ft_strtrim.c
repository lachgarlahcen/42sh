/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:10:14 by nsaber            #+#    #+#             */
/*   Updated: 2020/01/23 20:06:41 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		b;
	int		e;
	char	*p;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	b = i;
	while (s[i])
		i++;
	i--;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i > 0)
		i--;
	e = i;
	p = ft_strsub(s, b, ((e >= b) ? (e - b) : (b - e)) + 1);
	return (p);
}
