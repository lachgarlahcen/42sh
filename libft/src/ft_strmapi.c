/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:08:25 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 17:51:15 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*t;

	i = 0;
	if (s)
		if ((t = (char *)malloc(ft_strlen(s) + 1)) != NULL)
		{
			while (s[i])
			{
				t[i] = f(i, s[i]);
				i++;
			}
			t[i] = '\0';
			return (t);
		}
	return (NULL);
}
