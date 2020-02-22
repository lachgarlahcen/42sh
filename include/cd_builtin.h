/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:03:55 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/22 23:59:53 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_BUILTIN_H
# define CD_BUILTIN_H

# include "shell.h"
# include <sys/stat.h>

int			built_cd(char **args);
char		*path_of_link(char *dir, char *pwd);
int			isdir(char *path);

#endif
