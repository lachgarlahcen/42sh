/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:08:00 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/12 22:14:40 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	else
		return (0);
}
