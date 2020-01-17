/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:39:13 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/14 20:57:09 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	fill_from_histfile(void)
{
	int		fd;
	char	*line;

	fd = open(HISTORY_FILE_PATH, O_RDONLY);
	if (fd < 0)
		return ;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
		add_to_hist(line);
	close(fd);
}

void	init_history(void)
{
	t_hist	*hist;

	if ((hist = (t_hist *)malloc(sizeof(t_hist))) == NULL)
		exit(0);
	hist->tmp = NULL;
	hist->col = 0;
	hist->count = 0;
	hist->hist_list = NULL;
	save_hist(&hist);
	fill_from_histfile();
}

void	add_to_hist(char *cmd)
{
	t_hist *hist;
	t_data *new;
	t_data *tmp;

	hist = NULL;
	hist = save_hist(&hist);
	if (ft_strlen(cmd) == 0 || !hist)
	{
		free(cmd);
		return ;
	}
	if ((new = (t_data *)malloc(sizeof(t_data))) == NULL)
		return ;
	new->data = cmd;
	tmp = hist->hist_list;
	hist->hist_list = new;
	new->next = tmp;
	hist->count++;
}

void	fill_histfile(void)
{
	t_hist	*hist;
	int		fd;

	hist = NULL;
	hist = save_hist(&hist);
	if (!hist)
		return ;
	fd = open(HISTORY_FILE_PATH, O_FILL, S_IWUSR | S_IRUSR);
	if (fd < 0)
		return ;
	write_backword(fd, hist->hist_list);
	close(fd);
}

void	free_history(void)
{
	t_hist	*hist;
	t_data	*to_free;

	hist = NULL;
	hist = save_hist(&hist);
	if (!hist)
		return ;
	fill_histfile();
	while (hist->hist_list)
	{
		to_free = hist->hist_list;
		hist->hist_list = hist->hist_list->next;
		free(to_free->data);
		free(to_free);
	}
	if (hist->tmp)
		free(hist->tmp);
	free(hist);
}
