/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:44:59 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 12:53:59 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*t;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		t = (char *)malloc((len + 1) * sizeof(char *));
		if (t)
		{
			ft_strcpy(t, s1);
			ft_strcat(t, s2);
		}
		return (t);
	}
	return (NULL);
}
