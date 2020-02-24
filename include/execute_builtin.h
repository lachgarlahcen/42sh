/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:46:30 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 23:38:38 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BUILTIN_H
# define EXECUTE_BUILTIN_H

# include "shell.h"
# include "test_builtin.h"
# include "cd_builtin.h"

int		is_builtin(char *exec);
int		execute_builtin(char **args);

int64_t	ft_atoll(char *str, int *check);
int		ft_perror_buil(char *error);
#endif
