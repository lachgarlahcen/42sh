/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:15:21 by hastid            #+#    #+#             */
/*   Updated: 2019/11/18 06:06:18 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_form	*ft_init(void)
{
	t_form	*frm;

	if (!(frm = (t_form *)malloc(sizeof(t_form))))
		return (0);
	frm->fie = 0;
	frm->pre = 0;
	frm->poi = 0;
	if (!(frm->flag = ft_strdup("\0")))
		return (0);
	if (!(frm->leng = ft_strdup("\0")))
		return (0);
	return (frm);
}

int		printf_form_2(char **fmt, t_form **frm)
{
	if (!((*frm)->leng = ft_strjoin_free((*frm)->leng, **fmt)))
		return (0);
	if (!++(*fmt))
		return (0);
	if (**fmt && (**fmt == 'h' || **fmt == 'l'))
	{
		if (!((*frm)->leng = ft_strjoin_free((*frm)->leng, **fmt)))
			return (0);
		(*fmt)++;
	}
	return (1);
}

int		printf_form(char **fmt, t_form **frm)
{
	while (**fmt && (**fmt == '#' || **fmt == '0'
			|| **fmt == '+' || **fmt == '-' || **fmt == ' '))
	{
		if (!((*frm)->flag = ft_strjoin_free((*frm)->flag, **fmt)))
			return (0);
		(*fmt)++;
	}
	if (**fmt && ft_isdigit(**fmt))
		(*frm)->fie = nbr_cnvrt(fmt);
	if (**fmt && **fmt == '.')
	{
		(*frm)->poi = 1;
		(*fmt)++;
		if (ft_isdigit(**fmt))
			(*frm)->pre = nbr_cnvrt(fmt);
	}
	if (**fmt && (**fmt == 'h' || **fmt == 'l'))
		if (!printf_form_2(fmt, frm))
			return (0);
	if (!(**fmt))
		return (0);
	return (1);
}

int		printf_cnv(char c, va_list ap, t_form *frm)
{
	if (c == 's')
		return (ft_putstr_pr(va_arg(ap, char *), frm));
	else if (c == 'c')
		return (ft_putchar_pr(va_arg(ap, int), frm));
	else if (c == 'p')
		return (ft_putnbr_adr(va_arg(ap, uint64_t), frm));
	else if (c == 'd')
		return (ft_putwithleng(ap, frm));
	else if (c == 'i')
		return (ft_putwithleng(ap, frm));
	else if (c == 'u')
		return (ft_putuwithleng(ap, frm));
	else if (c == 'o')
		return (ft_putowithleng(ap, frm));
	else if (c == 'x')
		return (ft_putxwithleng(ap, frm));
	else if (c == 'X')
		return (ft_putcxwithleng(ap, frm));
	else if (c == '%')
		return (ft_putchar_pr('%', frm));
	return (0);
}

int		ft_printf(char *fmt, ...)
{
	int		l;
	t_form	*frm;
	va_list	ap;

	l = 0;
	if (fmt)
	{
		va_start(ap, fmt);
		while (*fmt)
		{
			if (*fmt == '%')
			{
				fmt++;
				if (!(frm = ft_init()) || !printf_form(&fmt, &frm))
					return (0);
				l += printf_cnv(*fmt, ap, frm);
				ft_free_st(frm);
			}
			else
				l += ft_putchar_ret(*fmt);
			fmt++;
		}
		va_end(ap);
	}
	return (l);
}
