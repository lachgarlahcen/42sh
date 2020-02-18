/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:52:00 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:01:00 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strmin(char **arr)
{
	size_t	size;
	size_t	min;
	int		i;

	if (arr == NULL)
		return (0);
	i = 0;
	min = ft_strlen(arr[0]);
	while (arr[i])
	{
		size = ft_strlen(arr[i]);
		min = size < min ? size : min;
	}
	return (min);
}
