/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:51:03 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/12 19:54:01 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *p;

	p = (char *)malloc(size + 1);
	if (!p)
		return (0);
	ft_bzero(p, size + 1);
	return (p);
}
