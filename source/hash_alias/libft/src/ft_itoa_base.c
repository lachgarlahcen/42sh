/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:10:41 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:59:41 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long	ll_abs(long long n)
{
	return (n >= 0 ? n : (-1) * n);
}

char		*convert_to_base(long long value, int base)
{
	int			i;
	int			sign;
	char		buffer[66];
	long long	n;
	char		*base_conv_chars;

	base_conv_chars = ft_strdup("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	n = value;
	sign = 0;
	if (sign > 0)
		sign = 1;
	i = 0;
	while (n == LLONG_MIN || ll_abs(n) >= base)
	{
		buffer[i] = base_conv_chars[ll_abs(n % base)];
		n = n / base;
		i++;
	}
	buffer[i++] = base_conv_chars[ABS(n)];
	if (sign == 1)
		buffer[i++] = '-';
	buffer[i] = '\0';
	free(base_conv_chars);
	return (ft_strdup(buffer));
}

char		*ft_itoa_base(long long value, int base)
{
	char	*res;
	char	*buffer;
	int		len;
	int		j;

	len = (int)ft_strlen(buffer);
	buffer = convert_to_base(value, base);
	res = (char *)malloc(sizeof(char) * (len + 1));
	len--;
	j = 0;
	while (len >= 0)
	{
		res[j] = buffer[len];
		len--;
		j++;
	}
	free(buffer);
	res[j] = '\0';
	return (res);
}
