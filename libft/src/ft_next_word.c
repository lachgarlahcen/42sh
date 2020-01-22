/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:00:17 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 16:59:50 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next_word(char *str, char *del, int reset_val)
{
	static int	i;
	int			j;
	char		*word;

	if (!str || !del || reset_val < -1)
		return (NULL);
	i = reset_val == LAST_POS ? i : reset_val;
	while (str[i])
	{
		if (ft_strchr(del, str[i]) == NULL)
		{
			j = i;
			while (ft_strchr(del, str[j]) == NULL && str[j])
				j++;
			word = ft_strnew(j - i);
			ft_strncpy(word, str + i, j - i);
			i = j;
			return (word);
		}
		i++;
	}
	return (NULL);
}
