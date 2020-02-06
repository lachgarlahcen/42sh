/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:36:34 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/16 23:31:45 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_list	*multifiles(t_list **head, int fd)
{
	t_list *temp;

	temp = *head;
	while (temp)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("", fd);
	ft_lstadd(head, temp);
	return (temp);
}

static int		find(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

int				next_line(t_list *temp, char **line, int res)
{
	if (ft_memchr(temp->content, '\n', ft_strlen(temp->content)))
	{
		res = find(temp->content, '\n');
		*line = ft_strsub(temp->content, 0, res);
		temp->content = ft_strchr(temp->content, '\n') + 1;
		return (1);
	}
	else if (res == 0 && ft_strcmp(temp->content, "\0"))
	{
		*line = temp->content;
		temp->content = "\0";
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*temp;
	char			buff[BUFF_SIZE + 1];
	int				res;

	if (fd < 0 || BUFF_SIZE < 0 || read(fd, buff, 0))
		return (-1);
	temp = multifiles(&head, fd);
	while ((res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[res] = '\0';
		if (!(temp->content = ft_strjoin(temp->content, buff)))
			return (-1);
		if (ft_memchr(temp->content, '\n', ft_strlen(temp->content)))
			break ;
	}
	if (next_line(temp, line, res) == 1)
		return (1);
	else
		return (0);
}
