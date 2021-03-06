/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:59:51 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 19:20:41 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int		ft_append(t_tok *tmp, char *file)
{
	int fd;

	if ((fd = ft_get_file_fd(file, 1)) < 0)
		return (-1);
	if (ft_get_id(tmp, 1))
	{
		if (dup2(fd, ft_atoi(ft_get_id(tmp, 1))) == -1)
		{
			ft_putendl_fd("42sh: bad file descriptor", 2);
			return (-1);
		}
		ft_check_close_fd(fd);
	}
	else
	{
		if (dup2(fd, 1) == -1)
		{
			ft_putendl_fd("42sh: bad file descriptor", 2);
			return (-1);
		}
		ft_check_close_fd(fd);
	}
	return (0);
}

int		ft_out_redirection(t_tok *tmp, char *file)
{
	int		fd;
	int		err;

	if (ft_strequ(ft_get_id(tmp, 2), ">") == 1)
	{
		if ((fd = ft_get_file_fd(file, 0)) < 0)
			return (-1);
		if (ft_get_id(tmp, 1))
			err = dup2(fd, ft_atoi(ft_get_id(tmp, 1)));
		else
			err = dup2(fd, 1);
		if (err == -1)
		{
			ft_putendl_fd("42sh: bad file descriptor", 2);
			return (-1);
		}
		ft_check_close_fd(fd);
	}
	else if (ft_strequ(ft_get_id(tmp, 2), ">>") == 1)
	{
		if (ft_append(tmp, file) == -1)
			return (-1);
	}
	return (0);
}

int		ft_in_redirection(t_tok *p, char *file)
{
	int i;

	if (ft_strequ(ft_get_id(p, 2), "<") == 1)
	{
		if (access(file, R_OK) == -1 && access(file, F_OK) == -1)
		{
			ft_putendl_fd("42sh: no such file or directory: ", 2);
			return (-1);
		}
		else if (access(file, R_OK) == -1)
		{
			ft_putendl_fd("42sh: permission denied: ", 2);
			return (-1);
		}
		if ((i = open(file, O_RDONLY)) == -1)
		{
			ft_putendl_fd("42sh: bad file", 2);
			return (-1);
		}
		dup2(i, 0);
		ft_check_close_fd(i);
	}
	return (0);
}

int		ft_duplication(t_tok *tmp, char *file)
{
	if (ft_out_redirection(tmp, file) == -1)
		return (1);
	else if (ft_ampersand(tmp, file) == -1)
		return (1);
	else if (ft_in_redirection(tmp, file) == -1)
		return (1);
	else if (ft_run_herdoc(tmp, file) == -1)
		return (1);
	else if (ft_aggregation(tmp, file) == -1)
		return (1);
	else if (ft_close_fd(tmp, file) == -1)
		return (1);
	return (0);
}

int		ft_redirection(t_proc *p)
{
	t_tok	*tmp;
	char	*file;

	tmp = p->red;
	while (tmp)
	{
		file = ft_get_id(tmp, 3);
		if (ft_get_id(tmp, 2))
		{
			if (ft_duplication(tmp, file) == 1)
				return (1);
		}
		while (tmp->id != 3)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (0);
}
