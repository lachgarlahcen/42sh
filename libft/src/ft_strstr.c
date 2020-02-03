/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 11:04:23 by hastid            #+#    #+#             */
/*   Updated: 2018/10/07 20:24:09 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hay, const char *nee)
{
	int i;

	if (!ft_strlen(nee))
		return ((char *)hay);
	while (*hay)
	{
		i = 0;
		while (*(hay + i) == nee[i] && *(hay + i))
			i++;
		if (!(nee[i]))
			return ((char *)hay);
		hay++;
	}
	return (NULL);
}
