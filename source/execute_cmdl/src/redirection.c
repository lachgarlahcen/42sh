/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:59:51 by hastid            #+#    #+#             */
/*   Updated: 2020/02/19 06:08:57 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int		ft_all_digits(char *str)
{
	if (ft_strlen(str) == 0)
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (0);
}

char	*ft_get_redict_by_id(t_proc *p, int i)
{
	t_tok *tmp;

	tmp = p->red;
	while (tmp)
	{
		if ((tmp)->id == i)
			return ((tmp)->token);
		(tmp) = (tmp)->next;
	}
	return (NULL);
}

int		ft_is_file(char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int		ft_get_file_fd(char *file, char append)
{
	int i;

	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
		{
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": Permission denied", 2);
			return (-1);
		}
		if (!ft_is_file(file))
		{
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": is not a file", 2);
			return (-1);
		}
	}
	if (append == 1)
	{
		i = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	}
	else
		i = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	return (i);
}

int		ft_out_redirection(t_proc *tmp)
{
	int		fd;

	if (ft_strequ(ft_get_redict_by_id(tmp, 2), ">") == 1)
	{
		if ((fd = ft_get_file_fd(ft_get_redict_by_id(tmp, 3), 0)) < 0)
			return (-1);
		if (ft_get_redict_by_id(tmp, 1))
			dup2(fd, ft_atoi(ft_get_redict_by_id(tmp, 1)));
		else
			dup2(fd, 1);
	}
	else if (ft_strequ(ft_get_redict_by_id(tmp, 2), ">>") == 1)
	{
		if ((fd = ft_get_file_fd(ft_get_redict_by_id(tmp, 3), 1)) < 0)
			return (-1);
		if (ft_get_redict_by_id(tmp, 1))
			dup2(fd, ft_atoi(ft_get_redict_by_id(tmp, 1)));
		else
			dup2(fd, 1);
	}
	return (0);
}

int		ft_ampersand(t_proc *p)
{
	int fd;

	if (ft_strequ(ft_get_redict_by_id(p, 2), "&>") == 1
						&& ft_get_redict_by_id(p, 3))
	{
		if ((fd = ft_get_file_fd(ft_get_redict_by_id(p, 3), 0)) < 0)
			return (-1);
		dup2(fd, 1);
		dup2(fd, 2);
	}
	if (ft_strequ(ft_get_redict_by_id(p, 2), ">&") == 1)
	{
		if (ft_get_redict_by_id(p, 3) &&
			!ft_all_digits(ft_get_redict_by_id(p, 3)))
		{
			if (ft_get_redict_by_id(p, 1) &&
					ft_all_digits(ft_get_redict_by_id(p, 1)) == 0)
				dup2(ft_atoi(ft_get_redict_by_id(p, 3)),
						ft_atoi(ft_get_redict_by_id(p, 1)));
			else
				dup2(ft_atoi(ft_get_redict_by_id(p, 3)), 1);
		}
	}
	return (0);
}

int		ft_redirection(t_proc *p)
{
	// ft_putendl(ft_get_redict_by_id(p, 1));
	// ft_putendl(ft_get_redict_by_id(p, 2));
	// ft_putendl(ft_get_redict_by_id(p, 3));
	if (ft_get_redict_by_id(p, 2))
	{
		if (ft_out_redirection(p) == -1)
			return (1);
		if (ft_ampersand(p) == -1)
			return (1);
	}
	return (0);
}
