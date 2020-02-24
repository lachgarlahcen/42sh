/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:23:41 by aihya             #+#    #+#             */
/*   Updated: 2020/02/23 21:01:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <sys/stat.h>
# include "intern_variables.h"

# define HT_LIMIT			20
# define TRUE				1
# define FALSE				0
# define INC				1
# define DEC				-1

typedef struct	s_htnode
{
	char			*name;
	char			*value;
	unsigned int	hits;
	struct s_htnode	*next;
}				t_htnode;

// Hashtable function
t_htnode	**init_hashtable(void);
t_htnode	*new_htnode(char *name, char *value);
void		print_hashtable(t_htnode **hashtable, char **names, char *prefix);
void		pop_htnode(t_htnode **hashtable, char *name);
void		push_htnode(t_htnode **hashtable, t_htnode **new);
t_htnode	*find_htnode(t_htnode **hashtable, char *name);
void		free_htnode(t_htnode **a_htnode);
int			hash_function(char *str);
char		**get_names(t_htnode **hashtable, size_t size);

// Aliases functions
int			alias(char **args);
t_htnode	**aliases(int init);
char		**aliases_names(int reset);
size_t		aliases_counter(int action);
char		*is_alias(char *name);
int			save_alias(char *name, char *value);
void		print_alias(char *name, int prefix);
void		print_all_alias(void);

// Unalias functions
int			unalias(char **args);
int			unalias_usage(void);

// Binaries functions
int			hash(char **args);
t_htnode	**binaries(int init);
char		**binaries_names(int reset);
size_t		binaries_counter(int action);
char		*is_binary(char *name);
int			save_binary(char *bin_name, char *bin_value);
void		remove_binary(char *name);
void		remove_binaries(void);
int			update_binary(char *name, char *new_value);
void        update_binaries(void);
void		print_binaries();
char		*get_base_name(char *path);
int			hash_usage(void);
void		hit_binary(char *name);
void		print_binaries(void);
int			is_path_like(char *str);
int			r_option(char **args, int *status, int* last_index);

// Error functions
int			err_msg(char *caller, char *target, char *msg);
int			invalid_option(char *arg, char target_option, char *caller);

// Sort function
void		sort(char **chain, size_t size);

// Type functions
int			type(char **args);

// Utils
char		*get_fullpath(char *basename, char *name);
char		*get_bin_path(char *bin_name);

// Expansions (simple form)
char		*expand(char *arg);

#endif
