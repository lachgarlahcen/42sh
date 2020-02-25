/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:35:28 by aihya             #+#    #+#             */
/*   Updated: 2020/02/25 04:18:10 by aihya            ###   ########.fr       */
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

	if (name == NULL)
		return (0);
	if ((alias = find_htnode(aliases(FALSE), name)) == NULL)
	{
		if ((alias = new_htnode(name, value)) == NULL)
			return (0);
		push_htnode(aliases(FALSE), &alias);
		aliases_counter(INC);
	}
	else
	{
		ft_strdel(&(alias->value));
		alias->value = ft_strdup(value);
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

char			**aliases_names(void)
{
	return (get_names(aliases(FALSE), aliases_counter(0)));
}
