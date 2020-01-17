/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:23:15 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 16:55:07 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *str1, const void *str2, int c, size_t n)
{
	char			*s1;
	const char		*s2;

	s1 = str1;
	s2 = str2;
	while (n--)
	{
		*s1++ = *s2;
		if (*s2 == (char)c)
			return ((void *)s1);
		s2++;
	}
	return (NULL);
}
