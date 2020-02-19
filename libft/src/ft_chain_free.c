/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chain_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:12:15 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:58:17 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		ft_chain_free(char ***a_chain)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_chain_size(*a_chain);
	while (i < size)
	{
		free((*a_chain)[i]);
		i++;
	}
	free(*a_chain);
	(*a_chain) = NULL;
}
