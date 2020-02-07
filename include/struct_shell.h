/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 00:32:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/07 02:28:22 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SHELL_H
# define STRUCT_SHELL_H

typedef struct	s_tok
{
	int				id;
	char			*token;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_var
{
	int				id;
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct	s_proc
{
	int				stat;
	t_tok			*as;
	t_tok			*red;
	struct s_proc	*next;
}				t_proc;

#endif
