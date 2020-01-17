/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:10:22 by hastid            #+#    #+#             */
/*   Updated: 2018/10/10 17:52:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t			l;
	char			*t;
	unsigned int	nbr;

	l = ft_nbrlen(n);
	if (n < 0)
		l++;
	if ((t = (char *)malloc(l + 1)) != NULL)
	{
		t[l--] = '\0';
		if (n == 0)
			t[0] = '0';
		if (n < 0)
			t[0] = '-';
		nbr = (n < 0) ? -n : n;
		while (nbr)
		{
			t[l--] = (unsigned char)((nbr % 10) + '0');
			nbr /= 10;
		}
		return (t);
	}
	return (NULL);
}
