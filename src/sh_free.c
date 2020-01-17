/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:56:42 by hastid            #+#    #+#             */
/*   Updated: 2019/12/23 20:18:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_memdel((void **)&tab[i++]);
		ft_memdel((void **)&tab);
	}
}

void	free_pipes(t_pipe *lst)
{
	t_pipe	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free_tokens(lst->tok);
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

void	free_tokens(t_tok *lst)
{
	t_tok	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->id == 10)
			close(ft_atoi(lst->next->value));
		ft_memdel((void **)&(lst->value));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

void	free_environ(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->name));
		ft_memdel((void **)&(lst->value));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}
