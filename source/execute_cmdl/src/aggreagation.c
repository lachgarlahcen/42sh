/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreagation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:42:27 by iel-bouh          #+#    #+#             */
/*   Updated: 2020/02/24 03:27:14 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int		ft_close_fd(t_tok *p, char *file)
{
	if (ft_strequ(ft_get_id(p, 2), ">&") ||
			ft_strequ(ft_get_id(p, 2), "<&"))
	{
		if (ft_strequ(file, "-"))
		{
			if (ft_get_id(p, 1) &&
					ft_all_digits(ft_get_id(p, 1)) == 0)
				close(ft_atoi(ft_get_id(p, 1)));
			else if (!ft_get_id(p, 1))
				close(1);
		}
	}
	return (0);
}

int		ft_normal_aggregation(char *file)
{
	if (dup2(ft_atoi(file), 1) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	close(ft_atoi(file));
	return (0);
}

int		ft_aggregation(t_tok *p, char *file)
{
	if (ft_strequ(ft_get_id(p, 2), ">&") || ft_strequ(ft_get_id(p, 2), "<&"))
	{
		if (file && !ft_all_digits(file))
		{
			if (ft_get_id(p, 1) &&
					!ft_all_digits(ft_get_id(p, 1)))
			{
				if (ft_check_fd(file, p) == -1)
					return (-1);
				if (dup2(ft_atoi(file),
						ft_atoi(ft_get_id(p, 1))) == -1)
				{
					ft_putendl_fd("42sh: bad file descriptor", 2);
					return (-1);
				}
				if (ft_atoi(file) > 2)
					close(ft_atoi(file));
			}
			else if (!ft_strequ(file, "-"))
			{
				if (ft_normal_aggregation(file) == -1)
					return (-1);
			}
		}
	}
	return (0);
}

int		ft_ampersand(t_tok *p, char *file)
{
	int fd;

	if ((ft_strequ(ft_get_id(p, 2), "&>")
		|| ft_strequ(ft_get_id(p, 2), ">&"))
							&& file)
	{
		if (ft_strequ(ft_get_id(p, 2), ">&") &&
				(ft_strequ(file, "-") || !ft_all_digits(file)))
			return (0);
		if ((fd = ft_get_file_fd(file, 0)) < 0)
			return (-1);
		if (dup2(fd, 1) == -1)
		{
			ft_putendl_fd("42sh: bad file descriptor", 2);
			return (-1);
		}
		if (dup2(fd, 2) == -1)
		{
			ft_putendl_fd("42sh: bad file descriptor", 2);
			return (-1);
		}
		close(fd);
	}
	return (0);
}
