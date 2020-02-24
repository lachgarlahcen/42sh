/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 23:37:00 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 23:37:36 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_builtin.h"

int			ft_perror_buil(char *error)
{
	ft_putstr("42sh: ");
	ft_putendl(error);
	return (1);
}

int64_t		ft_atoll(char *str, int *check)
{
	int			s;
	int			i;
	uint64_t	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		*check = (r > 9223372036854775807) ? 1 : 0;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
		*check = 1;
	return ((int64_t)(r * s));
}
