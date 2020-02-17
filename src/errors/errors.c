/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:08:27 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 18:14:26 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				err_msg(char *caller, char *target, char *msg)
{
	if (caller)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": ", 2);
	}
	if (target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int				invalid_option(char *arg, char target_option, char *caller)
{
	int		index;
	int		status;
	char	*option;

	if (ft_strequ(arg, "--"))
		return (0);
	status = 0;
	index = 1;
	while (arg[index])
	{
		if (arg[index] != target_option)
		{
			status = 1;
			break ;
		}
		index++;
	}
	if (status == 1)
	{
		option = NULL;
		ft_strappend(&option, arg[index], TRUE);
		err_msg(caller, option, "Invalid option");
		ft_strdel(&option);
	}
	return (status);
}