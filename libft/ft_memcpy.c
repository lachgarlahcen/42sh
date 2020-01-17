/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:23:15 by hastid            #+#    #+#             */
/*   Updated: 2018/10/07 19:47:53 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	size_t		i;
	char		*s1;
	const char	*s2;

	i = 0;
	s1 = str1;
	s2 = str2;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (str1);
}
