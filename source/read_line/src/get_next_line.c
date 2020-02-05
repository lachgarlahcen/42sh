/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:43:39 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:42:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static int		get_the_line(char **s, char **line, int fd)
{
	int		len;
	char	*tmp;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = s[fd];
		s[fd] = ft_strdup(s[fd] + len + 1);
		free(tmp);
	}
	else if (s[fd][len] == '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*s[256];
	char		buf[BUFF_SIZE + 1];
	int			r_res;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((r_res = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r_res] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		s[fd] = ft_strjoin_f(s[fd], buf, 1, 0);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (r_res < 0)
		return (-1);
	else if (r_res == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
	{
		if (s[fd])
			free(s[fd]);
		return (0);
	}
	return (get_the_line(s, line, fd));
}
