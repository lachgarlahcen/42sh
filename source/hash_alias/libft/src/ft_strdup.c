/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 22:19:49 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:00:43 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	s1_size;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	if (!(dup = (char *)malloc(sizeof(char) * (s1_size + 1))))
		return (NULL);
	i = 0;
	while (i < s1_size)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
