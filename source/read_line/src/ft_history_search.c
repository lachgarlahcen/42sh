/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:06:00 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 01:02:06 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** THIS FUNCTION GETS THE POS OF THE FIRST OCCERANCE
** IN HESTORY REORDES
** else it returns -1
*/

int			get_history_pos_by_match(char *patt)
{
	t_hist	*hist;
	t_data	*tmp;
	int		i;

	hist = NULL;
	hist = save_hist(&hist);
	tmp = hist->hist_list;
	i = 0;
	while (patt[0] && tmp)
	{
		if (ft_strstr(tmp->data, patt))
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

/*
** THIS FUNCTION REATURN THE FIRST PATTERN MATCHING STARTING FROM THE LAST CMD
** SUBMETED INTO HISTORY LIST IF NOTHIG IS FOUND THEN RETURN NULL
** PATT: PATTERN TO LOOK FOR IN HISTORY
*/

char		*get_history_by_match(char *patt)
{
	t_hist	*hist;
	t_data	*tmp;

	hist = NULL;
	hist = save_hist(&hist);
	tmp = hist->hist_list;
	while (patt[0] && tmp)
	{
		if (ft_strstr(tmp->data, patt))
			return (ft_strdup(tmp->data));
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** THIS FUNCTTION GETS CMD FROM HISTORY  BY IT'S POSTIONG AND IT TAKES 3
**  PARAMETERS:
** POS : THE POSTION OF THE ELEMENT STARTING FROM THE LAST SUBMITED CMD
** IF POST IS NEGATIVE IT START FROM THE FIRST ELEMENT
** PATT : THE WORD AFTER ! EX: IF !-2HELLO THE PATH IS "-2HELLO"
** TYPE : WHAT TYPE OF EXPENTION NUMBER (!2 !-2) POINT(!!)
*/

char		*get_history_by_pos(int pos, char *patt, int type)
{
	t_hist	*hist;
	char	*cmd;
	int		i;

	hist = NULL;
	hist = save_hist(&hist);
	i = -1;
	if (pos < 0)
		cmd = get_element_by_index((pos * -1) - 1, hist->hist_list);
	else if (pos > 0)
		cmd = get_element_by_index(hist->count - pos, hist->hist_list);
	else
		return (NULL);
	if (!cmd)
		return (NULL);
	cmd = ft_strdup(cmd);
	if (type == POINT)
		cmd = ft_strjoin_f(cmd, &patt[1], 1, 0);
	else
	{
		while (patt[++i] >= '0' && patt[i] <= '9')
			;
		cmd = ft_strjoin_f(cmd, &patt[i], 1, 0);
	}
	return (cmd);
}

/*
** THIS IS THE FIRST FUNCTION THAT FIRE WHEN SEARCHING IN HISTORY
** OR REAPLASING EXPAINTIONS LIKE !! !-NUM !NUMB !WORD
** IN CASE OF DIRECT SEARCH AND !WORD THE SAME THING RETURNED
*/

char		*search_history(char *patt)
{
	if (patt[0] == '!')
		return (get_history_by_pos(-1, patt, POINT));
	if (patt[0] > '0' && patt[0] <= '9')
		return (get_history_by_pos(ft_atoi(patt), patt, NUMBER));
	if (patt[0] == '-')
		return (get_history_by_pos(ft_atoi(patt), &patt[1], NUMBER));
	return (get_history_by_match(patt));
}
