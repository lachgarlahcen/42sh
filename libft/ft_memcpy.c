/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:49:32 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/11 19:20:08 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*ptr;
	char			*p2;

	i = 0;
	ptr = (char *)dst;
	p2 = (char *)src;
	while (i < n)
	{
		ptr[i] = p2[i];
		i++;
	}
	return (dst);
}
