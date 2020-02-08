/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:36:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/08 05:43:21 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_builtin.h"

int		execute_builtin(char **args)
{
/*	if (!ft_strcmp("cd", *args))
		execute_cd();
	else if (!ft_strcmp("fg", *args))
		execute_fg();
	else if (!ft_strcmp("bg", *args))
		execute_bg();
	else if (!ft_strcmp("fc", *args))
		execute_fd();
	else if (!ft_strcmp("set", *args))
		execute_set();
	else if (!ft_strcmp("echo", *args))
		execute_echo();
	else if (!ft_strcmp("exit", *args))
		execute_exit();
	else if (!ft_strcmp("type", *args))
		execute_type();
*/	if (!ft_strcmp("test", *args))
		execute_test(args);
/*	else if (!ft_strcmp("jobs", *args))
		execute_jobs();
	else if (!ft_strcmp("hash", *args))
		execute_hash();
	else if (!ft_strcmp("unset", *args))
		execute_unset();
	else if (!ft_strcmp("alias", *args))
		execute_alias();
	else if (!ft_strcmp("unalias", *args))
		execute_unalias();
	else
*/	return (0);
}
