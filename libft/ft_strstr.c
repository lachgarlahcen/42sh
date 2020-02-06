/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:50:13 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/09 14:09:45 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;

	if (*needle == '\0')
		return ((char *)haystack);
	if (*haystack == '\0')
		return (0);
	while (*haystack)
	{
		if (*haystack == needle[0])
		{
			i = 0;
			while (haystack[i] == needle[i] || needle[i] == '\0')
			{
				if (needle[i] == '\0')
					return ((char *)haystack);
				i++;
			}
		}
		haystack++;
	}
	return (0);
}
