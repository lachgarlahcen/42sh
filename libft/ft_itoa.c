/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 20:21:49 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/17 15:08:52 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static	char	*ft_myfonctionfiller(char *p, int i, int plus, unsigned int nbr)
{
	i = i + plus - 1;
	p[i + 1] = '\0';
	if (plus == 1)
		p[0] = '-';
	while ((plus == 1 ? i : i + 1) > 0)
	{
		p[i--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (p);
}

char			*ft_itoa(int n)
{
	char			*p;
	int				plus;
	int				i;
	unsigned int	nbr;
	unsigned int	k;

	plus = 0;
	i = 1;
	if (n < 0)
	{
		nbr = n * (-1);
		plus = 1;
	}
	else
		nbr = n;
	k = nbr;
	while (k >= 10)
	{
		k = k / 10;
		i++;
	}
	p = (char *)malloc((i + plus + 1));
	if (!p)
		return (0);
	return (ft_myfonctionfiller(p, i, plus, nbr));
}
