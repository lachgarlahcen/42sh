/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:33:52 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/09 14:11:49 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned	int	i;
	int				r;

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
