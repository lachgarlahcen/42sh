/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 00:07:54 by aihya             #+#    #+#             */
/*   Updated: 2020/01/10 17:32:20 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	s1_size;
	size_t	s2_size;
	size_t	i;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_size + s2_size + 1));
	i = 0;
	while (i < (s1_size + s2_size))
	{
		if (s1 && *s1)
		{
			result[i] = *s1;
			s1++;
		}
		else if (s2 && *s2)
		{
			result[i] = *s2;
			s2++;
		}
		i++;
	}
	result[i] = '\0';
	return (result);
}
