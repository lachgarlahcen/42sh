/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:18:33 by hastid            #+#    #+#             */
/*   Updated: 2018/10/12 12:55:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char	s[n];

	if (n > 65535)
		return (0);
	ft_memcpy(s, str2, n);
	ft_memcpy(str1, s, n);
	return (str1);
}
