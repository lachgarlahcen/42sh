/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:23:41 by aihya             #+#    #+#             */
/*   Updated: 2020/01/22 19:25:47 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# define LIMIT	100

typedef struct	s_htnode
{
	char	*name;
	char	*value;
	t_node	*next;
}				t_htnode;

typedef struct	s_data
{
	t_htnode	**aliases;
	t_htnode	**paths;
}				t_data;

#endif
