/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:00:19 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 17:50:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*t;

	i = 0;
	if (s)
		if ((t = (char *)malloc(ft_strlen(s) + 1)) != NULL)
		{
			while (s[i])
			{
				t[i] = f(s[i]);
				i++;
			}
			t[i] = '\0';
			return (t);
		}
	return (NULL);
}
