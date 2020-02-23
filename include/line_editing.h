/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 02:44:32 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 19:05:45 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "shell.h"

int		is_inhibitors(char c);
int		used_variable(char c);
int		free_return(char *str, int ret);
int		end_of_inhibitors(char *str, char c, int be);
int		ft_perror_line(char *str, char c, char *err, int f);
char	*strjoin_free(char *s1, char *s2, int f1, int f2);

int		syntax(char *str);
int		begin_syntax(char *str);
int		check_dollar_var(char *str, int be);
int		history_expa_syntax(char *str);
int		expansion_dollar(char *str);

char	*check_alias(char *line);
int		check_history_expa(char **line);
int		line_lexical(char **str, char **alias);

int		line_editing(char *line, int lexical);

#endif
