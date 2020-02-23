/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:34:13 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 00:45:09 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_err_ret(const char *str, int ret)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			write(2, &str[i++], 1);
	return (ret);
}

int		ft_putstr_ret(const char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			write(1, &str[i++], 1);
	return (i);
}
