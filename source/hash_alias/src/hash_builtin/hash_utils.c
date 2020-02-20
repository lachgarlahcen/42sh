/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:04:02 by aihya             #+#    #+#             */
/*   Updated: 2020/02/20 01:41:42 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_binaries(void)
{
	t_htnode	*node;
	char		**names;
	int			index;

	if (binaries_counter(0) == 0)
		return ;
	names = binaries_names(FALSE);
	index = 0;
	ft_printf("%-8s%s\n", "hits", "command");
	while (names[index])
	{
		node = find_htnode(binaries(FALSE), names[index]);
		ft_printf("%4d    %s\n", node->hits, node->value);
		index++;
	}
}

int		is_path_like(char *str)
{
	int		index;

	index = 0;
	if (ft_strlen(str) == 1 && str[0] == '.')
		return (1);
	while (str[index])
	{
		if (str[index] == '/')
			return (1);
		index++;
	}
	return (0);
}

int		r_option(char **args, int *status, int *last_index)
{
	int		i;
	int		remove_all;

	i = 0;
	remove_all = 0;
	while (args[i] && args[i][0] == '-' && ft_strlen(args[i]) > 1)
	{
		if (ft_strequ(args[i], "--") && (*last_index = ++i))
			break ;
		if (invalid_option(args[i], 'r', "hash"))
		{
			*status = hash_usage();
			break ;
		}
		remove_all = 1;
		*last_index = ++i;
	}
	return (remove_all);
}
