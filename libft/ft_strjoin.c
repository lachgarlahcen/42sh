/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:15:46 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/13 15:08:31 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	k = i;
	i = 0;
	while (s2[i])
	{
		p[k] = s2[i];
		i++;
		k++;
	}
	p[k] = '\0';
	return (p);
}
