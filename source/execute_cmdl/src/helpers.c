/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:45:16 by iel-bouh          #+#    #+#             */
/*   Updated: 2020/02/23 15:46:43 by iel-bouh         ###   ########.fr       */
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

char	*ft_get_redict_by_id(t_tok *tok, int i)
{
	t_tok *tmp;

	tmp = tok;
	while (tmp)
	{
		if ((tmp)->id == i)
			return ((tmp)->token);
		if ((tmp)->id == 3)
			break ;
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

	if (file[0] == '$')
	{
		ft_putstr_fd(file, 2);
		ft_putendl_fd("42sh: ambiguous redirect", 2);
		return (-1);
	}
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
		{
			ft_putstr_fd(file, 2);
			ft_putendl_fd("42sh: Permission denied", 2);
			return (-1);
		}
	}
	(append == 1) ? (i = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU))
				: (i = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU));
	if (i == -1)
	{
		ft_putendl_fd("42sh: bad file", 2);
		return (-1);
	}
	return (i);
}

int		ft_check_fd(char *str, t_tok *p)
{
	int			fd;
	struct stat s;

	if (fstat(fd = ft_atoi(str), &s) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	if (ft_strequ(ft_get_redict_by_id(p, 2), ">&") && write(fd, 0, 0) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	if (ft_strequ(ft_get_redict_by_id(p, 2), "<&") && read(fd, 0, 0) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	return (0);
}
