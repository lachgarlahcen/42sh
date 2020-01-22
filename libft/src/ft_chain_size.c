/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chain_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:48:49 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:58:26 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_chain_size(char **chain)
{
	size_t	size;

	if (chain == NULL)
		return (0);
	size = 0;
	while (chain[size] != NULL)
		size++;
	return (size);
}
