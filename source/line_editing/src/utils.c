/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 02:52:37 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 22:23:30 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		free_return(char *str, int ret)
{
	ft_memdel((void **)&str);
	return (ret);
}

int		ft_perror_line(char *str, char c, char *err, int f)
{
	ft_putstr_fd("42sh: ", 2);
	if (c)
		ft_putchar_fd(c, 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(err, 2);
	if (f)
		ft_memdel((void **)&str);
	exit_status(258, 1);
	return (1);
}

char	*strjoin_free(char *s1, char *s2, int f1, int f2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (f1)
		ft_memdel((void **)&s1);
	if (f2)
		ft_memdel((void **)&s2);
	return (str);
}

int		used_variable(char c)
{
	if (c == ';')
		return (1);
	if (c == '&' || c == '|')
		return (1);
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		end_of_inhibitors(char *str, char c, int be)
{
	int	i;

	i = be;
	if (c == '\\')
	{
		if (!str[i])
			return (-1);
		return (i + 1);
	}
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\\' && c == '\"')
			i++;
		i++;
	}
	if (!str[i])
		return (-2);
	return (i + 1);
}
