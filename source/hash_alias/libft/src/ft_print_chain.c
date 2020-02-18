/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chain.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:19:42 by aihya             #+#    #+#             */
/*   Updated: 2020/01/24 19:36:28 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_chain(char **chain, char *del)
{
	size_t	i;

	if (chain == NULL)
		return ;
	i = 0;
	while (chain[i])
	{
		ft_putstr(chain[i]);
		ft_putstr(del);
		i++;
	}
}
