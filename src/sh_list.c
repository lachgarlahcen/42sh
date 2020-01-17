/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 06:33:22 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 13:44:53 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static t_tok	*init_token(char *tmp, int id)
{
	t_tok	*token;

	if (!(token = (t_tok *)malloc(sizeof(t_tok))))
		return (0);
	token->id = id;
	if (!(token->value = ft_strdup(tmp)))
		return (0);
	token->next = 0;
	return (token);
}

int				save_tokens(t_tok **tok, char *token, int id)
{
	t_tok	*tmp;

	if (*tok)
	{
		tmp = *tok;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = init_token(token, id)))
			return (1);
	}
	else if (!((*tok) = init_token(token, id)))
		return (1);
	return (0);
}
