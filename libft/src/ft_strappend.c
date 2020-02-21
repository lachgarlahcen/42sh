/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:29:09 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 17:16:20 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strappend(char **a_s1, char c, int overwrite)
{
	char	*new;
	int		i;

	if ((new = (char *)malloc(sizeof(char) * (ft_strlen(*a_s1) + 2))) == NULL)
		return (NULL);
	i = 0;
	while ((*a_s1) && (*a_s1)[i])
	{
		new[i] = (*a_s1)[i];
		i++;
	}
	new[i] = c;
	new[++i] = '\0';
	if (overwrite == 1)
	{
		ft_strdel(a_s1);
		*a_s1 = new;
		return (NULL);
	}
	return (new);
}
