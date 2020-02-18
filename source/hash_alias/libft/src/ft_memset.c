/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:59:09 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:59:15 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_cpy;
	unsigned char	c_cpy;
	int				range;

	range = 0;
	b_cpy = (unsigned char *)b;
	c_cpy = (unsigned char)c;
	while (range < (int)len)
	{
		b_cpy[range] = c_cpy;
		range++;
	}
	return (b_cpy);
}
