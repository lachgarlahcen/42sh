/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:40:10 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 05:19:58 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMDL_H
# define EXECUTE_CMDL_H

# include "shell.h"
# include "struct_shell.h"

char	**get_args(t_tok *as);
char	*check_token_expan(char *str, char id);
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
void	ft_check_close_fd(int i);

int		ft_perror_pipe(char *error, int ret);
int		is_dir(char *di);
char	*search_executable(char *cmdl);
int		set_intern_variables(t_tok *as);

int		execute_without_fork(t_proc *p, int iv);
int		execute_pipes_line(t_proc *p, int bg);

#endif
