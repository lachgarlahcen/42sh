/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_filedis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:42:58 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 13:48:09 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		isdir(char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (dir != 0)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int		save_file(t_file **file, int in, int out, int err)
{
	if (!((*file) = (t_file *)malloc(sizeof(t_file))))
		return (1);
	if (((*file)->in = dup(in)) == -1)
		exit(1);
	if (((*file)->out = dup(out)) == -1)
		exit(1);
	if (((*file)->err = dup(err)) == -1)
		exit(1);
	return (0);
}

void	free_file(t_file *file)
{
	if (file)
	{
		if ((dup2(file->in, 0)) == -1)
			exit(1);
		if ((dup2(file->out, 1)) == -1)
			exit(1);
		if ((dup2(file->err, 2)) == -1)
			exit(1);
		close(file->in);
		close(file->out);
		close(file->err);
		ft_memdel((void **)&file);
	}
}

char	*add_to_file(char *file, char *s)
{
	char	*tmp1;
	char	*tmp2;

	if (!file || file[0] == '\0')
	{
		if (!s || s[0] == '\0')
			return (ft_strdup("\n"));
		return (ft_strjoin(s, "\n"));
	}
	if (!s || s[0] == '\0')
	{
		if (!(tmp1 = ft_strjoin(file, "\n")))
			return (0);
		ft_memdel((void **)&file);
		return (tmp1);
	}
	if (!(tmp1 = ft_strjoin(s, "\n")))
		return (0);
	if (!(tmp2 = ft_strjoin(file, tmp1)))
		return (0);
	ft_memdel((void **)&file);
	ft_memdel((void **)&tmp1);
	return (tmp2);
}
