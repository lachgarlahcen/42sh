/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/05 05:16:11 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		aff_tokens(t_tok *t)
{
	while (t)
	{
		printf("%d |%s|\n", t->id, t->token);
		t = t->next;
	}
}

int			execute_cmdline(char *line)
{
	t_tok *t;

	t = parse_tokens(line);
	aff_tokens(t);
	free_toks(t);
	return (0);
}
