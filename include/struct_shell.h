/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 00:32:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/06 02:28:44 by hastid           ###   ########.fr       */
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
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct	s_pipe
{
	t_tok			*as;
	t_tok			*red;
	struct s_pipe	*next;
}				t_pipe;

#endif
