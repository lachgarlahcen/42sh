/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 02:19:44 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:00:55 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_1;
	size_t	size_2;
	size_t	i;
	size_t	j;

	size_1 = ft_strlen(src) + size;
	size_2 = ft_strlen(src) + ft_strlen(dst);
	i = ft_strlen(dst);
	j = 0;
	while (src[j] != '\0' && size != 0 && i < (size - 1))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	if (size_2 > size_1)
		return (size_1);
	return (size_2);
}
