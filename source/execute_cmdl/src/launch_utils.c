/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:27:40 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 05:22:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int		set_intern_variables(t_tok *as)
{
	while (as)
	{
		set_variable(as->token, 0, 0);
		as = as->next;
	}
	return (exit_status(0, 1));
}

int		ft_perror_pipe(char *error, int ret)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putendl_fd(error, 2);
	return (ret);
}

int		is_dir(char *di)
{
	DIR	*d;

	if (!(d = opendir(di)))
		return (0);
	closedir(d);
	return (1);
}

void	ft_perror_execu(char *cmdl, char *err, int ex)
{
	ft_putstr_fd("42sh : ", 2);
	ft_putstr_fd(cmdl, 2);
	ft_putendl_fd(err, 2);
	exit(ex);
}

char	*search_executable(char *cmdl)
{
	char	*excu;

	if (!access(cmdl, F_OK))
		if (!access(cmdl, X_OK))
			if (!is_dir(cmdl))
				return (cmdl);
	if (!is_dir(cmdl))
	{
		excu = is_binary(cmdl);
		if (excu)
			return (excu);
		else if ((excu = get_bin_path(cmdl)))
			return (excu);
		ft_perror_execu(cmdl, ": command not found", 127);
	}
	else
		ft_perror_execu(cmdl, ": is a directory", 126);
	return (0);
}
