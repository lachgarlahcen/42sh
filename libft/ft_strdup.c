/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:12:20 by nsaber            #+#    #+#             */
/*   Updated: 2020/01/23 22:34:58 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *str)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	ptr = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (ptr)
	{
		i = 0;
		while (str[i] != '\0')
		{
			ptr[i] = str[i];
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (0);
}
