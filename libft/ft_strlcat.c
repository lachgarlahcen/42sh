/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 20:08:08 by hastid            #+#    #+#             */
/*   Updated: 2018/10/11 14:31:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			r;

	i = 0;
	while (dst[i] != '\0' && size > 0)
	{
		i++;
		size--;
	}
	r = i + ft_strlen(src);
	if (size > 0)
	{
		while (*src != '\0' && size > 1)
		{
			dst[i] = *src++;
			size--;
			i++;
		}
		dst[i] = '\0';
	}
	return (r);
}
