/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:35:28 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 19:42:18 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_htnode		**aliases(int init)
{
	static t_htnode	**hashtable;

	if (init == TRUE)
		hashtable = init_hashtable();
	return (hashtable);
}

size_t			aliases_counter(int action)
{
	static size_t	counter = 0;

	if (action == INC)
		counter++;
	else if (action == DEC && counter > 0)
		counter--;
	return (counter);
}

int				save_alias(char *name, char *value)
{
	t_htnode	*alias;

	if (name == NULL || value == NULL)
		return (0);
	alias = new_htnode(name, value);
	if (alias == NULL)
		return (0);
	if (push_htnode(aliases(FALSE), &alias))
	{
		aliases_counter(INC);
		aliases_names(TRUE);
	}
	return (1);
}

char			*is_alias(char *name)
{
	t_htnode	*alias;

	if ((alias = find_htnode(aliases(FALSE), name)) == NULL)
		return (NULL);
	return (alias->value);
}

char			**aliases_names(int reset)
{
	static char	**names = NULL;

	if (reset == TRUE)
	{
		if (names != NULL)
			ft_chain_free(&names);
		names = get_names(aliases(FALSE), aliases_counter(0));
	}
	return (names);
}
