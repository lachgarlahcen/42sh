/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 03:34:51 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:59:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ccpy;
	unsigned char	*p_s;

	ccpy = (unsigned char)c;
	p_s = (unsigned char *)s;
	if (n != 0)
	{
		while (n-- != 0)
			if (*p_s++ == ccpy)
				return ((void *)p_s - 1);
	}
	return (NULL);
}
