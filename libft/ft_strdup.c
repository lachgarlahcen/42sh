/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:45:30 by hastid            #+#    #+#             */
/*   Updated: 2019/12/06 03:47:20 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	l;
	char	*us;

	i = 0;
	l = ft_strlen(src);
	us = (char *)malloc(l + 1);
	if (us)
	{
		while (i < l)
		{
			us[i] = src[i];
			i++;
		}
		us[l] = '\0';
		return (us);
	}
	return (NULL);
}
