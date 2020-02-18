/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:53:16 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:15:22 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*get_base_name(char *path)
{
	char	*base_name;
	size_t	len;
	int		i;
	int		j;

	base_name = NULL;
	len = ft_strlen(path);
	i = len != 0 ? len - 1 : len;
	while (i >= 0 && path[i] != '/')
		i--;
	if (i != 0)
		i--;
	j = 0;
	while (j <= i)
	{
		ft_strappend(&base_name, path[j], TRUE);
		j++;
	}
	return (base_name);
}

static int	path_basenames_cmp(char *base_name)
{
	char	**table;
	int		index;
	int		match;
	char	*path_var;

	path_var = get_variable("PATH");
	match = 0;
	index = 0;
	table = ft_strsplit(path_var, ':');
	while (table[index])
	{
		if (ft_strequ(table[index], base_name))
		{
			match = 1;
			break ;
		}
		index++;
	}
	ft_strdel(&path_var);
	ft_chain_free(&table);
	return (match);
}

void		update_binaries(void)
{
	t_htnode	**hashtable;
	char		**names;
	char		*base_name;
	int			index;

	hashtable = binaries(FALSE);
	names = binaries_names(FALSE);
	index = 0;
	while (names[index])
	{
		base_name = get_base_name(is_binary(names[index]));
		if (path_basenames_cmp(base_name) == FALSE)
			remove_binary(names[index]);
		ft_strdel(&base_name);
		index++;
	}
	binaries_names(RESET);
}

int			update_binary(char *name, char *new_value)
{
	t_htnode	*node;

	if ((node = find_htnode(binaries(FALSE), name)) != NULL)
	{
		node->hits = 0;
		ft_strdel(&(node->value));
		node->value = new_value;
		return (1);
	}
	return (0);
}
