/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 07:50:20 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:58:55 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	signed_n(char **buf)
{
	char	*tmp;

	tmp = ft_strjoin("-", *buf);
	free(*buf);
	*buf = ft_strdup(tmp);
	free(tmp);
}

char	*exceptions(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	else
		return (NULL);
}

char	*ft_itoa(int n)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*buf;
	int		is_signed;
	char	*excep;

	if ((excep = exceptions(n)))
		return (excep);
	is_signed = 0;
	if ((n < 0 && (n = n * (-1))))
		is_signed = 1;
	buf = ft_strdup("");
	while (n)
	{
		tmp_1 = ft_ctos((n % 10) + 48);
		tmp_2 = ft_strjoin(tmp_1, buf);
		free(buf);
		buf = ft_strdup(tmp_2);
		free(tmp_2);
		free(tmp_1);
		n = n / 10;
	}
	if (is_signed)
		signed_n(&buf);
	return (buf);
}
