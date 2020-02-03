/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 18:14:43 by hastid            #+#    #+#             */
/*   Updated: 2018/10/08 13:49:39 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	v;
	char			*us;
	int				t;

	t = 0;
	v = c;
	us = (char *)str;
	while (*str)
	{
		if (*str == v)
		{
			us = (char *)str;
			t = 1;
		}
		str++;
	}
	if (*str || (*str == '\0' && v == '\0'))
		return ((char *)str);
	if (t)
		return (us);
	return (0);
}
