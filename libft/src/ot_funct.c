/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_funct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:22:15 by hastid            #+#    #+#             */
/*   Updated: 2019/11/18 06:06:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unbrleng(uint64_t n, int base)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

int		nbr_cnvrt(char **str)
{
	int i;
	int	pre;

	i = 0;
	pre = 0;
	while (ft_isdigit(**str))
	{
		pre = pre * 10 + (**str - '0');
		(*str)++;
	}
	return (pre);
}

int		check_f(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strjoin_free(char *str, char c)
{
	int		l;
	char	*s;

	l = ft_strlen(str);
	if (!(s = ft_strnew(l + 1)))
		return (0);
	s = ft_strcpy(s, str);
	s[l] = c;
	ft_memdel((void **)&str);
	return (s);
}

void	ft_free_st(t_form *frm)
{
	ft_memdel((void **)(&(frm->flag)));
	ft_memdel((void **)(&(frm->leng)));
	ft_memdel((void **)&frm);
}
