/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:40:10 by hastid            #+#    #+#             */
/*   Updated: 2020/02/24 03:28:50 by iel-bouh         ###   ########.fr       */
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

char	*delet_quotes(char *str);
int		ft_redirection(t_proc *p);
int		ft_close_fd(t_tok *p, char *file);
int		ft_normal_aggregation(char *file);
int		ft_aggregation(t_tok *p, char *file);
int		ft_all_digits(char *str);
char	*ft_get_id(t_tok *tok, int i);
int		ft_is_file(char *path);
int		ft_get_file_fd(char *file, char append);
int		ft_check_fd(char *str, t_tok *p);
void	ft_append_to_doc(char **join, char *buf);
int		ft_herdoc(char *file);
int		ft_run_herdoc(t_tok *tmp, char *file);
int		ft_ampersand(t_tok *p, char *file);

#endif
