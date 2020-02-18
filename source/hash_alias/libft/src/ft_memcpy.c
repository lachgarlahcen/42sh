/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 23:45:36 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:59:08 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_cpy;
	const char	*src_cpy;
	int			range;

	range = 0;
	dst_cpy = dst;
	src_cpy = src;
	while (range < (int)n)
	{
		dst_cpy[range] = src_cpy[range];
		range++;
	}
	return (dst_cpy);
}
