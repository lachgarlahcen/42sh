/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:35:48 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 17:03:19 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (n--)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			return (*s1 - *s2);
	}
	return (0);
}
