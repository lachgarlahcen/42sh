/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 04:13:05 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 23:47:43 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "sh.h"
# include "libft.h"
# include "read_line.h"
# include "job_control.h"
# include "line_editing.h"
# include "execute_cmdl.h"
# include "tokens_parser.h"
# include "shell_signals.h"
# include "execute_builtin.h"
# include "intern_variables.h"
# include "struct_shell.h"

# define READ_SIZE 1000000

int		init_fd(int fd);
int		exit_status(int status, int check);

#endif
