/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:41:07 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 16:24:17 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	set_arg(char *arg, int *status)
{
	int			isset;
	char		*bin_path;

	isset = 0;

	if (ft_strlen(arg) == 0 || (bin_path = get_bin_path(arg)) == NULL)
	{
		*status = err_msg("hash", arg, "Not found");
		return ;
	}
	if (update_binary(arg, bin_path) == FALSE)
	{
		if (save_binary(arg, bin_path) == FALSE)
			*status = err_msg("hash", arg, "Unable to saved (check memory)");
	}
}

static void	set_arguments(char **args, int *status)
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

int			hash(char **args)
{
	int		status;

	status = 0;
	if (ft_chain_size(args) == 1)
		print_binaries();
	else
		set_arguments(args + 1, &status);
	return (status);
}
