/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_dioux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 05:21:16 by hastid            #+#    #+#             */
/*   Updated: 2019/11/10 11:49:13 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putwithleng(va_list ap, t_form *frm)
{
	if (ft_strcmp("hh", frm->leng) == 0)
		return (ft_putnbr_pr((signed char)va_arg(ap, int), frm));
	else if (ft_strcmp("h", frm->leng) == 0)
		return (ft_putnbr_pr((short int)va_arg(ap, int), frm));
	else if (ft_strcmp("l", frm->leng) == 0)
		return (ft_putnbr_pr((long int)va_arg(ap, long int), frm));
	else if (ft_strcmp("ll", frm->leng) == 0)
		return (ft_putnbr_pr((long long int)va_arg(ap, long long int), frm));
	else
		return (ft_putnbr_pr((int)va_arg(ap, int), frm));
}

int		ft_putuwithleng(va_list ap, t_form *frm)
{
	if (ft_strcmp("hh", frm->leng) == 0)
		return (ft_putunbr_pr((unsigned char)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("h", frm->leng) == 0)
		return (ft_putunbr_pr((unsigned short)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("l", frm->leng) == 0)
		return (ft_putunbr_pr((unsigned long)va_arg(ap, unsigned long), frm));
	else if (ft_strcmp("ll", frm->leng) == 0)
		return (ft_putunbr_pr((unsigned long long)
					va_arg(ap, unsigned long long), frm));
	else
		return (ft_putunbr_pr((unsigned int)va_arg(ap, unsigned int), frm));
}

int		ft_putowithleng(va_list ap, t_form *frm)
{
	if (ft_strcmp("hh", frm->leng) == 0)
		return (ft_putonbr_pr((unsigned char)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("h", frm->leng) == 0)
		return (ft_putonbr_pr((unsigned short)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("l", frm->leng) == 0)
		return (ft_putonbr_pr((unsigned long)va_arg(ap, unsigned long), frm));
	else if (ft_strcmp("ll", frm->leng) == 0)
		return (ft_putonbr_pr((unsigned long long)
					va_arg(ap, unsigned long long), frm));
	else
		return (ft_putonbr_pr((unsigned)va_arg(ap, unsigned), frm));
}

int		ft_putxwithleng(va_list ap, t_form *frm)
{
	if (ft_strcmp("hh", frm->leng) == 0)
		return (ft_putxnbr_pr((unsigned char)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("h", frm->leng) == 0)
		return (ft_putxnbr_pr((unsigned short)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("l", frm->leng) == 0)
		return (ft_putxnbr_pr((unsigned long)va_arg(ap, unsigned long), frm));
	else if (ft_strcmp("ll", frm->leng) == 0)
		return (ft_putxnbr_pr((unsigned long long)
					va_arg(ap, unsigned long long), frm));
	else
		return (ft_putxnbr_pr((unsigned)va_arg(ap, unsigned), frm));
}

int		ft_putcxwithleng(va_list ap, t_form *frm)
{
	if (ft_strcmp("hh", frm->leng) == 0)
		return (ft_putcxnbr_pr((unsigned char)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("h", frm->leng) == 0)
		return (ft_putcxnbr_pr((unsigned short)va_arg(ap, unsigned), frm));
	else if (ft_strcmp("l", frm->leng) == 0)
		return (ft_putcxnbr_pr((unsigned long)va_arg(ap, unsigned long), frm));
	else if (ft_strcmp("ll", frm->leng) == 0)
		return (ft_putcxnbr_pr((unsigned long long)
					va_arg(ap, unsigned long long), frm));
	else
		return (ft_putcxnbr_pr((unsigned)va_arg(ap, unsigned), frm));
}
