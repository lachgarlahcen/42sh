/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:03:55 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/23 21:53:14 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_BUILTIN_H
# define CD_BUILTIN_H

# include "shell.h"
# include <sys/stat.h>

int			built_cd(char **args);
char		*path_of_link(char *dir, char *pwd);
int			isdir(char *path);
int         change_dir_b(char *dir);
int         change_dir_a(char *dir);
int         change_dir(char *dir);
int			isdir(char *path);
int			ft_perror_cd(char *s, char *str, int ret);

#endif
