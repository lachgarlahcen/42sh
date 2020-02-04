/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 02:44:32 by hastid            #+#    #+#             */
/*   Updated: 2020/02/05 00:51:21 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "shell.h"

int		is_inhibitors(char c);
int		used_variable(char c);
int		free_return(char *str, int ret);
int		end_of_inhibitors(char *str, char c, int be);
int		ft_perror(char *str, char c, char *err, int f);
char	*strjoin_free(char *s1, char *s2, int f1, int f2);

int		syntax(char *str);
char	*check_alias(char *line);
int		check_history_expa(char **line);
int		line_lexical(char **str, char **alias);

int		line_editing(char **line, int lexical);

#endif
