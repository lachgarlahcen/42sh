/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:02:27 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:00:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	m;

	m = 1;
	if (n == -2147483648)
	{
		n /= 10;
		ft_putnbr_fd(n, fd);
		write(fd, "8", 1);
	}
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = n * (-1);
		}
		if (n / 10)
			ft_putnbr_fd(n / 10, fd);
		m = (n % 10) + 48;
		write(fd, &m, 1);
	}
}
