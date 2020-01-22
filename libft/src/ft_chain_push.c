/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chain_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 02:59:51 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:58:22 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		ft_chain_push(char ***a_chain, char *entry)
{
	char	**new;
	size_t	size;
	size_t	i;

	size = ft_chain_size(*a_chain);
	new = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup((*a_chain)[i]);
		i++;
	}
	new[i] = ft_strdup(entry);
	i++;
	new[i] = NULL;
	ft_chain_free(a_chain);
	*a_chain = new;
}
