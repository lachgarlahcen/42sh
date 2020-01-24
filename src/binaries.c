/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:04:02 by aihya             #+#    #+#             */
/*   Updated: 2020/01/24 20:36:30 by aihya            ###   ########.fr       */
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

int		save_binary(char *bin_name, char *bin_value)
{
	t_htnode	*bin;

	if (bin_name == NULL || bin_value == NULL)
		return (0);
	bin = new_htnode(bin_name, bin_value);
	if (bin == NULL)
		return (0);
	if (push_htnode(binaries(FALSE), &bin))
	{
		binaries_counter(INC);
		binaries_names(TRUE);
	}
	return (1);
}

char	*is_binary(char *name)
{
	t_htnode	*path;

	if ((path = find_htnode(binaries(FALSE), name)) == NULL)
		return (NULL);
	return (path->value);
}

void	remove_binary(char *name)
{
	pop_htnode(binaries(FALSE), name);
	if (binaries_counter(0) > 0)
		binaries_counter(DEC);
}

char			**binaries_names(int reset)
{
	static char	**names = NULL;

	if (reset == TRUE)
	{
		if (names != NULL)
			ft_chain_free(&names);
		names = get_names(binaries(FALSE), binaries_counter(0));
	}
	return (names);
}

void			print_binaries()
{
	print_hashtable(binaries(FALSE), binaries_names(FALSE), NULL);
}