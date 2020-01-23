/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:23:41 by aihya             #+#    #+#             */
/*   Updated: 2020/01/23 23:37:36 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# define HT_LIMIT	20
# define TRUE		1
# define FALSE		0

typedef struct	s_htnode
{
	char			*name;
	char			*value;
	struct s_htnode	*next;
}				t_htnode;

typedef struct	s_data
{
	t_htnode	**aliases;
	t_htnode	**paths;
}				t_data;

t_htnode	**init_hashtable();
t_htnode	*new_htnode(char *name, char *value);
void		print_hashtable(t_htnode **hashtable);
void		pop_htnode(t_htnode **hashtable, char *name);
void		push_htnode(t_htnode **hashtable, t_htnode **new);
t_htnode	*find_htnode(t_htnode **hashtable, char *name);
void		free_htnode(t_htnode **a_htnode);
int			hash_function(char *str);

// Aliases functions
t_htnode	**aliases(int init);
int			save_alias(char *name, char *value);
char		*is_alias(char *name);
void		unalias(char *name);

// Binaries functions
t_htnode	**binaries(int init);
int			save_binary(char *bin_name, char *bin_value);
char		*is_binary(char *name);
void		remove_binary(char *name);

#endif
