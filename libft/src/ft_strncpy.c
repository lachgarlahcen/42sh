/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 04:23:29 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:01:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	const char		*src_c;
	char			*dst_c;
	unsigned int	i;

	src_c = src;
	dst_c = dst;
	i = 0;
	while (i < (unsigned int)len && src_c[i] && (dst_c[i] = src_c[i]))
		i++;
	while (i < (unsigned int)len)
	{
		dst_c[i] = '\0';
		i++;
	}
	return (dst_c);
}
