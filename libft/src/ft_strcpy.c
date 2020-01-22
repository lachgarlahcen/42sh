/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 00:29:17 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:00:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	const char	*srccpy;
	char		*dstcpy;

	srccpy = src;
	dstcpy = dst;
	while ((*dstcpy++ = *srccpy++))
		;
	return (dst);
}
