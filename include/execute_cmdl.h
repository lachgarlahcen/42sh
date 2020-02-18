/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:18:12 by hastid            #+#    #+#             */
/*   Updated: 2020/02/18 06:30:56 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMDL_H
# define EXECUTE_CMDL_H

# include "shell.h"
# include "struct_shell.h"

int		change_expansion(t_tok *t);
int		check_fork(t_proc *p, int bg);

char	**get_args(t_tok *as);
int		check_all_arguments(t_proc *p);
void	free_tab(char **tab);

int		add_process(t_proc **pipes);
void	free_process(t_proc *pipes);

int		execute_cmdline(char *line);

#endif
