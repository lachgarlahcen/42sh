/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_lookup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:48:55 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:20:04 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_fullpath(char *basename, char *name)
{
	char	*fullpath;

	fullpath = ft_strappend(&basename, '/', FALSE);
	ft_strojoin(&fullpath, name, TRUE);
	return (fullpath);
}

char	*get_bin_path(char *bin_name)
{
	struct stat	st;
	char		*path_var;
	char		**basenames;
	char		*fullpath;
	int			index;

	path_var = get_variable("PATH");
	basenames = ft_strsplit(path, ':');
	index = 0;
	while (basenames[index])
	{
		fullpath = get_fullpath(basenames[index], bin_name);
		if (stat(fullpath, &st) == 0)
		{
			ft_chain_free(&basenames);
			ft_strdel(&path_var);
			return (fullpath);
		}
		ft_strdel(&fullpath);
		index++;
	}
	ft_chain_free(&basenames);
	ft_strdel(&path_var);
	return (NULL);
}
