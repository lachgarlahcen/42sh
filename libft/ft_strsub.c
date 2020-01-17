/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:28:35 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 12:42:17 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*t;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned char)ft_strlen(s))
		return (NULL);
	t = (char *)malloc((len + 1) * sizeof(char));
	if (!t)
		return (NULL);
	while (i++ < start)
		s++;
	i = 0;
	while (i < len && *s)
		t[i++] = *s++;
	t[i] = '\0';
	return (t);
}
