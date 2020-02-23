/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:43:39 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 22:08:17 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#include "libft.h"

static t_list	*file(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	if (!(tmp = ft_lstnew("\0", fd)))
		return (NULL);
	ft_lstadd(file, tmp);
	return (tmp);
}

static char		*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*us;

	i = 0;
	us = (char *)malloc(n + 1);
	if (us)
	{
		while (i < n)
		{
			us[i] = src[i];
			i++;
		}
		us[i] = '\0';
		return (us);
	}
	return (NULL);
}

static char		*ft_line(char *s, char **line)
{
	size_t	l;
	char	*t;

	l = 0;
	while (s[l] != '\n' && s[l])
		l++;
	if (!(*line = ft_strndup(s, l)))
		return (NULL);
	if (ft_strlen(s) > l)
	{
		if (!(t = ft_strdup(s + l + 1)))
			return (NULL);
		ft_memdel((void **)&s);
		s = t;
	}
	else
		ft_bzero(s, l);
	return (s);
}

int				get_next_line(const int fd, char **line)
{
	int				r;
	char			*t;
	char			buf[BUFF_SIZE + 1];
	t_list			*p_fd;
	static t_list	*resv;

	if (fd < 0 || line == NULL || !(*line = "\0") || read(fd, buf, 0) < 0)
		return (-1);
	if (!(p_fd = file(&resv, fd)))
		return (-1);
	while ((r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (!(t = ft_strjoin(p_fd->content, buf)))
			return (-1);
		ft_memdel((void **)&(p_fd->content));
		p_fd->content = t;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (r < BUFF_SIZE && !ft_strlen(p_fd->content))
		return (0);
	if (!(p_fd->content = ft_line(p_fd->content, line)))
		return (-1);
	return (1);
}
