/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_csp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 06:00:49 by hastid            #+#    #+#             */
/*   Updated: 2019/11/18 06:01:22 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putchar_pr(char c, t_form *frm)
{
	int	i;

	i = 0;
	if (check_f(frm->flag, '-') == 0)
	{
		if (check_f(frm->flag, '0'))
			while (i++ < frm->fie - 1)
				ft_putchar('0');
		else
			while (i++ < frm->fie - 1)
				ft_putchar(' ');
	}
	ft_putchar(c);
	if (check_f(frm->flag, '-'))
		while (i++ < frm->fie - 1)
			ft_putchar(' ');
	return (i);
}

int		ft_putstr_pr(char *str, t_form *frm)
{
	int	i;
	int	l;

	str = (str == 0) ? "(null)" : str;
	i = 0;
	l = ft_strlen(str);
	l = (l > frm->pre && frm->poi) ? frm->pre : l;
	if (check_f(frm->flag, '-') == 0)
	{
		if (check_f(frm->flag, '0'))
			while (i++ < frm->fie - l)
				ft_putchar('0');
		else
			while (i++ < frm->fie - l)
				ft_putchar(' ');
	}
	if (frm->poi)
		while (frm->pre-- > 0 && *str)
			ft_putchar(*str++);
	else
		ft_putstr(str);
	if (check_f(frm->flag, '-'))
		while (i++ < frm->fie - l)
			ft_putchar(' ');
	return (l + i - 1);
}

void	ft_putnbr_base(uint64_t nbr, unsigned int base, int check)
{
	if (nbr >= base)
		ft_putnbr_base(nbr / base, base, check);
	if ((nbr % base) < 10)
		ft_putchar('0' + nbr % base);
	else
	{
		if (check)
			ft_putchar('a' + nbr % base - 10);
		else
			ft_putchar('A' + nbr % base - 10);
	}
}

int		ft_putnbr_adr(uint64_t n, t_form *frm)
{
	int	i;
	int l;

	i = 0;
	l = ft_unbrleng(n, 16) + 2;
	if (check_f(frm->flag, '-') == 0 && check_f(frm->flag, '0') == 0)
		while (i++ < frm->fie - l)
			ft_putchar(' ');
	ft_putstr("0x");
	if (check_f(frm->flag, '0'))
		while (i++ < frm->fie - l)
			ft_putchar('0');
	ft_putnbr_base(n, 16, 1);
	if (check_f(frm->flag, '-'))
		while (i++ < frm->fie - l)
			ft_putchar(' ');
	return (l + i - 1);
}

int		ft_putall(t_form *frm, uint64_t n, int base, int max)
{
	int		l;
	int		ret;

	ret = 0;
	l = ft_unbrleng(n, base);
	if (frm->poi && frm->pre > l)
		while (frm->pre-- > l)
			ret += ft_putchar_ret('0');
	if (frm->poi == 0 && check_f(frm->flag, '0') && !check_f(frm->flag, '-'))
		while (frm->fie-- > max)
			ret += ft_putchar_ret('0');
	if (!(frm->poi && n == 0))
	{
		ret += l;
		if (base == 17)
			ft_putnbr_base(n, 16, 0);
		else
			ft_putnbr_base(n, base, 1);
	}
	if (check_f(frm->flag, '-'))
		while (frm->fie-- > max)
			ret += ft_putchar_ret(' ');
	return (ret);
}
