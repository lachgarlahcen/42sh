/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:23:19 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 17:53:28 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	l;
	char	*t;

	i = 0;
	if (s)
	{
		l = ft_strlen(s);
		while ((*s == ' ' || *s == '\t' || *s == '\n') && *s)
		{
			s++;
			l--;
		}
		while ((s[l - 1] == ' ' || s[l - 1] == '\t' || s[l - 1] == '\n') && *s)
			l--;
		if ((t = (char *)malloc(l + 1)) != NULL)
		{
			while (i < l)
				t[i++] = *s++;
			t[i] = '\0';
			return (t);
		}
	}
	return (NULL);
}
