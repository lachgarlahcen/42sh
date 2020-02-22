/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:59:51 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 16:17:14 by iel-bouh         ###   ########.fr       */
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
		// if (!ft_is_file(file))
		// {
		// 	ft_putstr_fd(file, 2);
		// 	ft_putendl_fd(": is not a file", 2);
		// 	return (-1);
		// }
	}
	if (append == 1)
	{
		if ((i = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
			ft_putendl_fd("42sh: bad file", 2);
	}
	else
	{
		if ((i = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			ft_putendl_fd("42sh: bad file", 2);
	}
	return (i);
}

int		ft_out_redirection(t_tok *tmp)
{
	int		fd;

	if (ft_strequ(ft_get_redict_by_id(tmp, 2), ">") == 1)
	{
		if ((fd = ft_get_file_fd(ft_get_redict_by_id(tmp, 3), 0)) < 0)
			return (-1);
		if (ft_get_redict_by_id(tmp, 1))
		{
			if (dup2(fd, ft_atoi(ft_get_redict_by_id(tmp, 1))) == -1)
				ft_putendl_fd("42sh: bad file descriptor", 2);
		}
		else
		{
			if (dup2(fd, 1) == -1)
				ft_putendl_fd("42sh: bad file descriptor", 2);
		}
	}
	else if (ft_strequ(ft_get_redict_by_id(tmp, 2), ">>") == 1)
	{
		if ((fd = ft_get_file_fd(ft_get_redict_by_id(tmp, 3), 1)) < 0)
			return (-1);
		if (ft_get_redict_by_id(tmp, 1))
		{
			if (dup2(fd, ft_atoi(ft_get_redict_by_id(tmp, 1))) == -1)
				ft_putendl_fd("42sh: bad file descriptor", 2);
		}
		else
		{
			if (dup2(fd, 1) == -1)
				ft_putendl_fd("42sh: bad file descriptor", 2);
		}
	}
	return (0);
}

int		ft_check_fd(char *str)
{
	int fd;
	struct stat s;

	if (fstat(fd = ft_atoi(str), &s) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	if (write(fd, 0, 0) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	if (read(fd, 0, 0) == -1)
	{
		ft_putendl_fd("42sh: bad file descriptor", 2);
		return (-1);
	}
	return (0);
}

int		ft_right_ampersand(t_tok *p)
{
	if (ft_get_redict_by_id(p, 3) &&
			!ft_all_digits(ft_get_redict_by_id(p, 3)))
	{
		if (ft_get_redict_by_id(p, 1) &&
				!ft_all_digits(ft_get_redict_by_id(p, 1)))
		{
			if (ft_check_fd(ft_get_redict_by_id(p, 3)) == -1)
				return (-1);
			if (dup2(ft_atoi(ft_get_redict_by_id(p, 3)),
					ft_atoi(ft_get_redict_by_id(p, 1))) == -1)
			{
				ft_putendl_fd("42sh: bad file descriptor", 2);
				return (-1);
			}
		}
		else
		{
			if (dup2(ft_atoi(ft_get_redict_by_id(p, 3)), 1) == -1)
			{
				ft_putendl_fd("42sh: bad file descriptor", 2);
				return (-1);
			}
		}
	}
	else if (ft_strequ(ft_get_redict_by_id(p, 3), "-"))
	{
		if (ft_get_redict_by_id(p, 1) &&
				ft_all_digits(ft_get_redict_by_id(p, 1)) == 0)
			close(ft_atoi(ft_get_redict_by_id(p, 1)));
		else if (!ft_get_redict_by_id(p, 1))
			close(1);
	}
	return (0);
}

int		ft_ampersand(t_tok *p)
{
	int fd;

	if (ft_strequ(ft_get_redict_by_id(p, 2), "&>") == 1
						&& ft_get_redict_by_id(p, 3))
	{
		if ((fd = ft_get_file_fd(ft_get_redict_by_id(p, 3), 0)) < 0)
			return (-1);
		if (dup2(fd, 1) == -1)
			ft_putendl_fd("42sh: bad file descriptor", 2);
		if (dup2(fd, 2) == -1)
			ft_putendl_fd("42sh: bad file descriptor", 2);
	}
	if (ft_strequ(ft_get_redict_by_id(p, 2), ">&") == 1)
	{
		if (ft_right_ampersand(p) == -1)
			return (-1);
	}
	return (0);
}

int		ft_in_redirection(t_tok *p)
{
	int i;

	if (ft_strequ(ft_get_redict_by_id(p, 2), "<") == 1)
	{
		if (access(ft_get_redict_by_id(p, 3), R_OK) == -1)
		{
			if (access(ft_get_redict_by_id(p, 3), F_OK) == -1)
			{
				ft_putstr_fd("42sh: no such file or directory: ", 2);
				return (-1);
			}
			else
			{
				ft_putstr_fd("42sh: permission denied: ", 2);
				return (-1);
			}
			// ft_putendl_fd(ft_get_redict_by_id(p, 3), 2);
		}
		if ((i = open(ft_get_redict_by_id(p, 3), O_RDONLY)) == -1)
		{
			ft_putendl_fd("42sh: bad file", 2);
			return (-1);
		}
		dup2(i, 0);
	}
	return (0);
}

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

int		ft_herdoc(t_tok *p)
{
	int		fd[2];
	char	*tmp;
	char	*join;

	join = NULL;
	pipe(fd);
	while (1)
	{
		tmp = read_line(">");
		if (!tmp || ft_strequ(tmp, ft_get_redict_by_id(p, 3)))
		{
			free(tmp);
			if (dup2(ft_stop_append_return(&join,
					ft_get_redict_by_id(p, 3), fd), 0) == -1)
				ft_putendl_fd("42sh: bad file descriptor", 2);
			return (0);
		}
		else
			ft_append_to_doc(&join, tmp);
	}
	return (0);
}

int		ft_redirection(t_proc *p)
{
	t_tok *tmp;

	tmp = p->red;
	while (tmp)
	{
			// ft_putendl(ft_get_redict_by_id(tmp, 1));
			// ft_putendl(ft_get_redict_by_id(tmp, 2));
			// ft_putendl(ft_get_redict_by_id(tmp, 3));
		if (ft_get_redict_by_id(tmp, 2))
		{
			if (ft_out_redirection(tmp) == -1)
				return (1);
			else if (ft_ampersand(tmp) == -1)
				return (1);
			else if (ft_in_redirection(tmp) == -1)
				return (1);
			else if (ft_strequ(ft_get_redict_by_id(tmp, 2), "<<") == 1
								&& ft_herdoc(tmp) == -1)
				return (1);
		}
		while (tmp->id != 3)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (0);
}
