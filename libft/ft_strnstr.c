/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 11:55:42 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 21:16:14 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nee, size_t len)
{
	size_t i;
	size_t l;

	l = ft_strlen(nee);
	if (!l)
		return ((char *)hay);
	while (*hay && len--)
	{
		i = 0;
		while (*(hay + i) == nee[i] && *(hay + i) && len - i + 1)
		{
			i++;
			if (nee[i] == '\0')
				return ((char *)hay);
		}
		hay++;
	}
	return (NULL);
}
