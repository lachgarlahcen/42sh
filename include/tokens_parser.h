/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 01:21:58 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 01:46:09 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_PARSER_H
# define TOKENS_PARSER_H

# include "shell.h"
# include "struct_shell.h"

int		save_tokens(t_tok **tok, char *token, int id);

t_tok	*parse_tokens(char *line);

void	free_toks(t_tok *lst);

int		is_number(char *str);
int		change_tokens(t_tok *tok);

#endif
