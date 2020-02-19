/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:40:10 by hastid            #+#    #+#             */
/*   Updated: 2020/02/19 03:40:16 by hastid           ###   ########.fr       */
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

int		ft_redirection(t_proc *p);

#endif
