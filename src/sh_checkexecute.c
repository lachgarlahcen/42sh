/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_checkexecute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 08:40:11 by hastid            #+#    #+#             */
/*   Updated: 2019/12/23 19:25:35 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int			heredirect(char *fin)
{
	int		pi[2];
	char	*s2;
	char	*tmp;
	char	*file;

	file = 0;
	s2 = read_line(">");
	if (pipe(pi) == -1)
		return (ft_perror(0, "fork failed", -1));
	while (fin && s2 && ft_strcmp(fin, s2))
	{
		(*s2 == '\n') ? *s2 = '\0' : 0;
		if (!(tmp = add_to_file(file, s2)))
			return (-1);
		file = tmp;
		ft_memdel((void **)&s2);
		s2 = read_line(">");
	}
	ft_memdel((void **)&s2);
	if (file)
		write(pi[1], file, ft_strlen(file));
	if (file)
		ft_memdel((void **)&file);
	close(pi[1]);
	return (pi[0]);
}

static int	ret_fildis(int rd, char *file, int n_id)
{
	if ((rd == 6 || rd == 9) && n_id != 1)
		return (!ft_strcmp(file, "-") ? -3 : ft_atoi(file));
	else if (rd == 5 || (rd == 6 && n_id == 1) || rd == 11)
		return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644));
	else if (rd == 8 || (rd == 9 && n_id == 1) || rd == 12)
		return (open(file, O_RDONLY));
	else if (rd == 7)
		return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0644));
	else if (rd == 10)
		return (ft_atoi(file));
	return (-1);
}

int			duplicate_file(char *fd, int rd, char *file, int n_id)
{
	int	fir;
	int	sec;

	if ((sec = ret_fildis(rd, file, n_id)) == -1)
		return (ft_perror(0, "open failed", 1));
	if (fd)
		fir = ft_atoi(fd);
	else if (rd == 5 || rd == 6 || rd == 7 || rd == 11)
		fir = 1;
	else if (rd == 8 || rd == 9 || rd == 10 || rd == 12)
		fir = 0;
	if (sec == -3)
		close(fir);
	else
	{
		if (dup2(sec, fir) == -1)
			return (ft_perror(0, "duplicate failed", 1));
		if (rd == 11 || rd == 12 || rd == 6 || rd == 9)
			if (dup2(sec, 2) == -1)
				return (ft_perror(0, "duplicate failed", 1));
		if (sec != 0 && sec != 1 && sec != 2)
			close(sec);
	}
	return (0);
}

int			duplicate(t_tok *toks)
{
	t_tok	*prev;

	if (!toks)
		return (0);
	prev = toks;
	while (toks)
	{
		if (toks->id > 4 && toks->id < 13)
			if (check_error_red(prev, toks))
				return (1);
		prev = toks;
		toks = toks->next;
	}
	return (0);
}

int			execute_tok(t_tok *t, t_env **env)
{
	char	*excu;
	char	**args;
	char	**environ;

	while (t && t->id != 0)
		t = t->next;
	if (!t)
		return (1);
	if (!(excu = search_executable(t->value, *env)))
		return (1);
	if (!(args = args_execve(t)))
		return (1);
	environ = list_to_tab(*env);
	if (execve(excu, args, environ) == -1)
		ft_perror(0, "exceve failed", 1);
	ft_memdel((void **)&excu);
	free_tab(args);
	free_tab(environ);
	return (0);
}
