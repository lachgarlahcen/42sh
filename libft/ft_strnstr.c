/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:50:13 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/11 13:39:07 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	int i;
	int size2;

	if (*needle == '\0' || *haystack == '\0')
		return (*needle == '\0' ? (char *)haystack : 0);
	while (*haystack && size-- > 0)
	{
		if (*haystack == needle[0])
		{
			i = 0;
			size2 = size;
			while (haystack[i] == needle[i] || needle[i] == '\0')
			{
				if (needle[i] == '\0')
					return ((char *)haystack);
				i++;
				if (size2 == 0 && needle[i] != '\0')
					return (0);
				size2--;
			}
		}
		haystack++;
	}
	return (0);
}
