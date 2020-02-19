/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:18:12 by hastid            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/02/19 02:17:44 by iel-bouh         ###   ########.fr       */
=======
/*   Updated: 2020/02/18 05:11:35 by iel-bouh         ###   ########.fr       */
>>>>>>> 47716197e0ff6e9e0249cbed3b68caa72bf94ac0
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
