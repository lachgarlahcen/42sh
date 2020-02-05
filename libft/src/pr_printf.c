/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:18:46 by hastid            #+#    #+#             */
/*   Updated: 2019/11/18 06:04:05 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_pr(int64_t nb, t_form *frm)
{
	int			l;
	int			max;
	int			ret;
	uint64_t	n;

	ret = 0;
	n = (nb < 0) ? -nb : nb;
	l = ft_unbrleng(n, 10);
	max = (l > frm->pre) ? l : frm->pre;
	if (max == frm->pre && nb == 0)
		frm->pre++;
	if (frm->fie >= l && nb == 0 && frm->pre == 0 && frm->poi)
		frm->fie++;
	if (nb < 0 || check_f(frm->flag, '+') || check_f(frm->flag, ' '))
		frm->fie--;
	if (!check_f(frm->flag, '-') && (!check_f(frm->flag, '0') || frm->poi))
		while (frm->fie-- > max)
			ret += ft_putchar_ret(' ');
	if (nb < 0)
		ret += ft_putchar_ret('-');
	else if (check_f(frm->flag, '+'))
		ret += ft_putchar_ret('+');
	else if (check_f(frm->flag, ' '))
		ret += ft_putchar_ret(' ');
	return (ret += ft_putall(frm, n, 10, max));
}

int		ft_putunbr_pr(uint64_t n, t_form *frm)
{
	int l;
	int	max;
	int	ret;

	ret = 0;
	l = ft_unbrleng(n, 10);
	max = (l > frm->pre) ? l : frm->pre;
	if (max == frm->pre && n == 0)
		frm->pre++;
	if (frm->fie >= l && n == 0 && frm->pre == 0 && frm->poi)
		frm->fie++;
	if (!check_f(frm->flag, '-') && (!check_f(frm->flag, '0') || frm->poi))
		while (frm->fie-- > max)
			ret += ft_putchar_ret(' ');
	ret += ft_putall(frm, n, 10, max);
	return (ret);
}

int		ft_putonbr_pr(int64_t n, t_form *frm)
{
	int	l;
	int	max;
	int ret;

	ret = 0;
	l = ft_unbrleng(n, 8);
	max = (l > frm->pre) ? l : frm->pre;
	if (check_f(frm->flag, '#') && n != 0 && frm->pre <= l)
		frm->fie--;
	if (max == frm->pre && n == 0)
		frm->pre++;
	if (frm->fie >= l && !n && !frm->pre && frm->poi &&
			!check_f(frm->flag, '#'))
		frm->fie++;
	if (!check_f(frm->flag, '-') && (!check_f(frm->flag, '0') || frm->poi))
		while (frm->fie-- > max)
			ret += ft_putchar_ret(' ');
	if (check_f(frm->flag, '#') && (n != 0 || frm->poi) && frm->pre <= l)
		ret += ft_putchar_ret('0');
	ret += ft_putall(frm, n, 8, max);
	return (ret);
}

int		ft_putxnbr_pr(int64_t n, t_form *frm)
{
	int	l;
	int	max;
	int ret;

	ret = 0;
	l = ft_unbrleng(n, 16);
	max = (l > frm->pre) ? l : frm->pre;
	if (check_f(frm->flag, '#') && !(frm->poi && n == 0) && n != 0)
		frm->fie -= 2;
	if (max == frm->pre && n == 0)
		frm->pre++;
	if (frm->fie >= l && n == 0 && frm->pre == 0 && frm->poi)
		frm->fie++;
	if (!check_f(frm->flag, '-') && (!check_f(frm->flag, '0') || frm->poi))
		while (frm->fie-- > max)
			ret += ft_putchar_ret(' ');
	if (check_f(frm->flag, '#') && !(frm->poi && n == 0) && n != 0)
		ret += ft_putstr_ret("0x");
	ret += ft_putall(frm, n, 16, max);
	return (ret);
}

int		ft_putcxnbr_pr(int64_t n, t_form *frm)
{
	int l;
	int	max;
	int ret;

	ret = 0;
	l = ft_unbrleng(n, 16);
	max = (l > frm->pre) ? l : frm->pre;
	if (check_f(frm->flag, '#') && !(frm->poi && n == 0) && n != 0)
		frm->fie -= 2;
	if (max == frm->pre && n == 0)
		frm->pre++;
	if (frm->fie >= l && n == 0 && frm->pre == 0 && frm->poi)
		frm->fie++;
	if (!check_f(frm->flag, '-') && (!check_f(frm->flag, '0') || frm->poi))
		while (frm->fie-- > max)
			ret += ft_putchar_ret(' ');
	if (check_f(frm->flag, '#') && !(frm->poi && n == 0) && n != 0)
		ret += ft_putstr_ret("0X");
	ret += ft_putall(frm, n, 17, max);
	return (ret);
}
