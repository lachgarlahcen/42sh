/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:41:02 by aihya             #+#    #+#             */
/*   Updated: 2020/02/25 03:19:11 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_htnode	**binaries(int init)
{
	static t_htnode	**hashtable;

	if (init == TRUE)
		hashtable = init_hashtable();
	return (hashtable);
}

size_t		binaries_counter(int action)
{
	static size_t	counter = 0;

	if (action == INC)
		counter++;
	else if (action == DEC && counter > 0)
		counter--;
	return (counter);
}

char		**binaries_names(void)
{
	return (get_names(binaries(FALSE), binaries_counter(0)));
}

char		*is_binary(char *name)
{
	t_htnode	*path;

	if ((path = find_htnode(binaries(FALSE), name)) == NULL)
		return (NULL);
	return (path->value);
}
