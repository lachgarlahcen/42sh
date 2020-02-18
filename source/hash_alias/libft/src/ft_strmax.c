/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:49:31 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:00:59 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strmax(char **arr)
{
	size_t	size;
	size_t	max;
	int		i;

	i = 0;
	max = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			size = ft_strlen(arr[i]);
			max = size > max ? size : max;
			i++;
		}
	}
	return (max);
}
