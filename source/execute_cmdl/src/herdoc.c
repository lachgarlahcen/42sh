/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:48:12 by iel-bouh          #+#    #+#             */
/*   Updated: 2020/02/23 15:53:12 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

void		ft_append_to_doc(char **join, char *buf)
{
	char *tmp;

	if (*join == NULL)
	{
		*join = ft_strdup(buf);
		free(buf);
	}
	else
	{
		tmp = ft_strjoin(*join, "\n");
		ft_memdel((void **)&(*join));
		*join = ft_strdup(tmp);
		ft_memdel((void **)&tmp);
		tmp = ft_strjoin(*join, buf);
		free(buf);
		ft_memdel((void **)&(*join));
		*join = ft_strdup(tmp);
		ft_memdel((void **)&tmp);
	}
}

int			ft_stop_append_return(char **join, char *stop, int p[2])
{
	char *tmp;

	if (*join)
	{
		tmp = ft_strjoin(*join, "\n");
		ft_memdel((void **)&(*join));
		*join = ft_strdup(tmp);
		ft_memdel((void **)&tmp);
		write(p[1], *join, ft_strlen(*join));
		ft_memdel((void **)&(*join));
	}
	close(p[1]);
	ft_memdel((void **)&stop);
	return (p[0]);
}

int			ft_herdoc(char *file)
{
	int		fd[2];
	char	*tmp;
	char	*join;

	join = NULL;
	pipe(fd);
	while (1)
	{
		tmp = read_line(">");
		if (!tmp || ft_strequ(tmp, file))
		{
			free(tmp);
			if (dup2(ft_stop_append_return(&join,
					file, fd), 0) == -1)
			{
				ft_putendl_fd("42sh: bad file descriptor", 2);
				return (-1);
			}
			return (0);
		}
		else
			ft_append_to_doc(&join, tmp);
	}
	return (0);
}
