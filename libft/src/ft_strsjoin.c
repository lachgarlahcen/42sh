/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:55:30 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:01:13 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsjoin(const char *s1, const char *s2, const char *dl)
{
	char	*result;
	size_t	s1_size;
	size_t	s2_size;
	size_t	dl_size;
	size_t	i;

	if (!s1 || !s2 || !dl)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	dl_size = ft_strlen(dl);
	result = (char *)malloc(sizeof(char) * (s1_size + s2_size + dl_size + 1));
	i = 0;
	while (i < (s1_size + s2_size + dl_size))
	{
		if (*s1 && s1++)
			result[i] = *(s1 - 1);
		else if (*dl && dl++)
			result[i] = *(dl - 1);
		else if (*s2 && s2++)
			result[i] = *(s2 - 1);
		i++;
	}
	result[i] = '\0';
	return (result);
}
