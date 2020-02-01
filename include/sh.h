/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:23:41 by aihya             #+#    #+#             */
/*   Updated: 2020/02/01 20:23:21 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
#include <sys/stat.h>

# define HT_LIMIT	20
# define TRUE		1
# define FALSE		0
# define INC		1
# define DEC		-1

typedef struct	s_htnode
{
	char			*name;
	char			*value;
	unsigned int	hits;
	struct s_htnode	*next;
}				t_htnode;

typedef struct	s_data
{
	t_htnode	**aliases;
	t_htnode	**paths;
}				t_data;

t_htnode	**init_hashtable();
t_htnode	*new_htnode(char *name, char *value);
void		print_hashtable(t_htnode **hashtable, char **names, char *prefix);
void		pop_htnode(t_htnode **hashtable, char *name);
int			push_htnode(t_htnode **hashtable, t_htnode **new);
t_htnode	*find_htnode(t_htnode **hashtable, char *name);
void		free_htnode(t_htnode **a_htnode);
int			hash_function(char *str);
char		**get_names(t_htnode **hashtable, size_t size);

// Aliases functions
t_htnode	**aliases(int init);
char		**aliases_names(int reset);
int			save_alias(char *name, char *value);
char		*is_alias(char *name);
void		unalias(char *name);
void		print_alias();

// Binaries functions
t_htnode	**binaries(int init);
char		**binaries_names(int reset);
int			save_binary(char *bin_name, char *bin_value);
char		*is_binary(char *name);
void		remove_binary(char *name);
void		remove_binaries();
void		print_binaries();

// Sort function
void	sort(char **chain, size_t size);

// Type functions
void	type(char **args);

#endif
