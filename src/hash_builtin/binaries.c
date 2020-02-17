/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:04:02 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 23:12:27 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			print_binaries(void)
{
	t_htnode	*node;
	char		**names;
	int			index;

	if (binaries_counter(0) == 0)
		return ;
	names = binaries_names(FALSE);
	index = 0;
	printf("%-8s%s\n", "hits", "command");
	while (names[index])
	{
		node = find_htnode(binaries(FALSE), names[index]);
		printf("%4d    %s\n", node->hits, node->value);
		index++;
	}
}

int				is_path_like(char *str)
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

static int		r_option(char **args, int *status, int* last_index)
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

char			*get_fullpath(char *basename, char *name)
{
	char	*fullpath;
	
	fullpath = ft_strappend(&basename, '/', FALSE);
	ft_strojoin(&fullpath, name, TRUE);
	return (fullpath);
}

void			set_arg(char *arg, int *status)
{
	struct stat	st;
	char		**basenames;
	char		*path = "/usr/bin:/bin";
	char		*fullpath;
	int			index;
	int			isset;

	isset = 0;
	basenames = ft_strsplit_del(path, ":");
	index = 0;
	fullpath = NULL;
	while (basenames[index])
	{
		fullpath = get_fullpath(basenames[index], arg);
		if (stat(fullpath, &st) == 0 && (isset = 1))
		{
			if (update_binary(arg, fullpath))
				break ;
			if (save_binary(arg, fullpath) == 0 && !(isset = 0))
				*status = err_msg("hash", fullpath, "Cannot be saved");
			break ;
		}
		ft_strdel(&fullpath);
		index++;
	}
	ft_strdel(&fullpath);
	if (*status == 0 && isset == 0)
		err_msg("hash", arg, "Not found");
}

static void		set_arguments(char **args, int *status)
{
	int		remove_all;
	int		index;

	index = 0;
	remove_all = r_option(args, status, &index);
	if (*status)
		return ;
	if (remove_all)
		remove_binaries();
	while (args[index])
	{
		if (is_path_like(args[index]) && ++index)
			continue ;
		else
			set_arg(args[index], status);
		index++;
	}
}

int				hash(char **args)
{
	int		status;

	status = 0;
	if (ft_chain_size(args) == 1)
		print_binaries();
	else
		set_arguments(args + 1, &status);
	return (status);
}

// int				set_arg(char *arg)
// {
// 	struct stat	st;
// 	char		**basenames;
// 	char		*path = "/usr/bin:/bin";
// 	char		*fullpath;
// 	int			index;
// 	int			isset;

// 	isset = 0;
// 	basenames = ft_strsplit_del(path, ":");
// 	index = 0;
// 	fullpath = NULL;
// 	while (basenames[index])
// 	{
// 		fullpath = ft_strjoin(basenames[index], arg);
// 		if (stat(fullpath, &st) == 0 && (isset = 1))
// 		{
// 			if (update_binary(arg, fullpath))
// 				break ;
// 			if (save_binary(arg, fullpath) == 0 && (isset = 0))
// 				err_msg("hash", fullpath, "Cannot be saved");
// 			break ;
// 		}
// 		index++;
// 	}
// 	ft_strdel(&fullpath);
// 	return (isset);
// }

// int				hash(char **args)
// {
// 	int		index;
// 	int		status;

// 	index = 1;
// 	while (args[index])
// 	{
// 		if (index == 1 && args[index][0] == '-' && ft_strlen(args[index]) > 1)
// 		{
// 			if (invalid_option(args[index], 'r', "hash"))
// 				return (hash_usage());
// 			remove_binaries();
// 		}
// 		else if (is_path_like(args[index]) && (status = 1))
// 			dprintf(2, "hash: %s: not found\n", args[index]);
// 		else
// 			status = set_arg(args[index]) == 0 ? 1 : status;
// 		index++;
// 	}
// 	return (0);
// }
