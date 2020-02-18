/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 19:50:05 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:59:01 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	c_c;
	unsigned char	*dst_c;
	unsigned char	*src_c;

	if (n)
	{
		c_c = (unsigned char)c;
		dst_c = (unsigned char *)dst;
		src_c = (unsigned char *)src;
		while (n--)
		{
			if ((*dst_c++ = *src_c++) == c_c)
				return (dst_c);
		}
	}
	return (NULL);
}
