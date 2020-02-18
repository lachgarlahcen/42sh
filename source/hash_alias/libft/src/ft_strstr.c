/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 00:07:14 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:01:16 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if ((!haystack && !needle) || !ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		if (!ft_strncmp(haystack + i, needle, ft_strlen(needle)))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
