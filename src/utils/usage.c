/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:14:54 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 19:45:51 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	hash_usage(void)
{
	return (err_msg("hash", "usage", "hash [-r] name [name ...]"));
}

int	unalias_usage(void)
{
	return (err_msg("unalias", "usage", "unalias [-a] name [name ...]"));
}
