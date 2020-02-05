/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 05:39:04 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:42:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char			*ft_strjoin_f(char *s1, char *s2, int a, int b)
{
	char	*str;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_strcpy(str, (char *)s1);
	ft_strcat(str, (char *)s2);
	if (a)
		free(s1);
	if (b)
		free(s2);
	return (str);
}

void	free_out(t_cmd *l)
{
	if (l)
	{
		ft_bzero(l->chars, BUFF_SIZE);
		if (l->cur_p)
			free(l->cur_p);
		if (l->init_p)
			free(l->init_p);
		free(l);
		keep_l(NULL, 0);
	}
	ft_putchar('\n');
}

void	go_to_the_end(t_cmd *l)
{
	l->cur = l->len;
	print_cmd(l);
}
