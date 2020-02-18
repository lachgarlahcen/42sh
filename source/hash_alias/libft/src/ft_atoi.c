/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:12:26 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:57:37 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		n;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	sign = 1;
	if ((str[i] == '-' && (sign = -1)) || str[i] == '+')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (!ft_isdigit(str[i]) || str[i] == '\0')
		return (0);
	n = 0;
	while (ft_isdigit(str[i]))
		n = (n * 10) + (str[i++] - 48);
	return (n * sign);
}
