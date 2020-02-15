/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:04:02 by aihya             #+#    #+#             */
/*   Updated: 2020/02/15 19:54:31 by aihya            ###   ########.fr       */
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
		binaries_names(RESET);
	}
	return (1);
}

char	*is_binary(char *name)
{
	t_htnode	*path;

	if ((path = find_htnode(binaries(FALSE), name)) == NULL)
		return (NULL);
	path->hits++;
	return (path->value);
}

void	remove_binary(char *name)
{
	pop_htnode(binaries(FALSE), name);
	if (binaries_counter(0) > 0)
		binaries_counter(DEC);
}

void	remove_binaries()
{
	char	**names;
	int		i;

	names = binaries_names(FALSE);
	i = 0;
	while (names[i])
	{
		remove_binary(names[i]);
		i++;
	}
}

char			*get_base_name(char *path)
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

static int		path_basename_cmp(char *base_name)
{
	char	**table;
	int		index;
	int		ret;
	char	*path = "/usr/bin:/bin";

	ret = 0;
	index = 0;
	table = ft_strsplit(path, ':');
	while (table[index])
	{
		if (ft_strequ(table[index], base_name))
		{
			ret = 1;
			break ;
		}
		index++;
	}
	ft_chain_free(&table);
	return (ret);
}

void			update_binaries()
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
		if (path_basename_cmp(base_name) == FALSE)
			remove_binary(names[index]);
		index++;
	}
	binaries_names(RESET);
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
	t_htnode	*node;
	char		**names;
	int			index;

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

char			invalid_options(char *arg)
{
	int	index;

	index = 1;
	while (arg[index])
	{
		if (arg[index] != 'r')
			return (arg[index]);
		index++;
	}
	return (0);
}

int				hash_usage(char c)
{
	dprintf(2, "hash: -%c: invalid option\n", c);
	dprintf(2, "hash: usage: hash [-r] name\n");
	return (1);
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

int				update_binary(char *name, char *new_value)
{
	t_htnode	*node;

	if ((node = find_htnode(binaries(FALSE), name)) != NULL)
	{
		node->hits = 0;
		ft_strdel(&(node->value));
		node->value = ft_strdup(new_value);
		return (1);
	}
	return (0);
}

// Needs get_variable function.
void			set_arg(char *arg)
{
	struct stat	st;
	char		**basenames;
	char		*path = "/usr/bin:/bin";
	char		*fullpath;
	int			index;
	int			set;

	set = 0;
	basenames = ft_strsplit_del(path, ":");
	index = 0;
	fullpath = NULL;
	while (basenames[index])
	{
		fullpath = ft_strjoin(basenames[index], arg);
		if (stat(fullpath, &st) == 0)
		{
			if (update_binary(arg, fullpath))
				break ;
			if (save_binary(arg, fullpath) == 0)
				dprintf("hash: Could not save %s\n", fullpath);
			break ;
		}
		index++;
	}
	ft_strdel(&fullpath);
}

int				hash(char **args)
{
	int		index;
//	char	*name;
//	char	*value;
	char	c;
	int		status;

	index = 1;
	while (args[index])
	{
		if (index == 1 && args[index][0] == '-' && ft_strlen(args[index]) > 1)
		{
			if ((c = invalid_options(args[index])))
				return (hash_usage(c));
			remove_binaries();
		}
		else if (is_path_like(args[index]) && (status = 1))
			dprintf(2, "hash: %s: not found\n", args[index]);
		else
			set_arg(args[index]);
		index++;
	}
	return (0);
}