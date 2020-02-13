/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:46:30 by hastid            #+#    #+#             */
/*   Updated: 2020/02/13 04:23:34 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BUILTIN_H
# define EXECUTE_BUILTIN_H

# include "shell.h"
# include "test_builtin.h"

int		is_builtin(char *exec);
int		execute_builtin(char **args);

#endif
