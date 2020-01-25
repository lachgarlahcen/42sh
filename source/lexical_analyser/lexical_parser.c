/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:47:13 by hastid            #+#    #+#             */
/*   Updated: 2020/01/23 23:51:19 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

static t_tok	*init_token(char *tmp, int id)
{
	t_tok	*token;

	if (!(token = (t_tok *)malloc(sizeof(t_tok))))
		return (0);
	token->id = id;
	if (!(token->tok = ft_strdup(tmp)))
		return (0);
	token->next = 0;
	return (token);
}

int				save_tokens(t_tok **tok, char *token)
{
	t_tok	*tmp;

	if (!token)
		return (0);
	if (*tok)
	{
		tmp = *tok;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = init_token(token, 0)))
			return (1);
	}
	else if (!((*tok) = init_token(token, 0)))
		return (1);
	ft_memdel((void **)&token);
	return (0);
}

void			free_toks(t_tok *lst)
{
	t_tok	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->tok));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}
