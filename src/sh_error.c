/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 14:40:52 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int			ft_perror(char *s, char *str, int ret)
{
	ft_putstr_fd("21sh: ", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putendl_fd(str, 2);
	return (ret);
}

static int	ft_error_0(char *val)
{
	int	fd;

	fd = ft_atoi(val);
	if (fd != 0 && fd != 1 && fd != 2)
	{
		if (dup2(1, fd) == -1)
			return (ft_perror(val, ": Bad file descriptor", 1));
		close(ft_atoi(val));
	}
	return (0);
}

static int	ft_error_1(t_tok tok, int n, char *rd)
{
	int			i;
	struct stat	s;

	if (tok.id != 2)
	{
		if (tok.value[0] == '\0')
			return (ft_perror(rd, ": Bad file descriptor", 1));
		if (n == 9 || (rd && ft_strcmp("1", rd)))
			return (ft_perror(tok.value, ": ambiguous redirect", 1));
		i = 0;
		while (tok.value[i + 1])
			i++;
		if (tok.value[i] == '-')
			return (ft_perror(tok.value, ": ambiguous redirect", 1));
	}
	if (tok.id == 2)
	{
		if (fstat(i = ft_atoi(tok.value), &s) == -1)
			return (ft_perror(tok.value, ": Bad file descriptor", 1));
		if (n == 6 && write(i, 0, 0) == -1)
			return (ft_perror(tok.value, ": Permission denied", 1));
		if (n == 9 && read(i, 0, 0) == -1)
			return (ft_perror(tok.value, ": Permission denied", 1));
	}
	return (0);
}

static int	ft_error_2(t_tok tok, int n)
{
	if (tok.value[0] == '\0')
		return (ft_perror(tok.value, ": No such file or directory", 1));
	if ((n == 5 || n == 7 || n == 11) && !access(tok.value, F_OK))
		if (access(tok.value, W_OK) == -1)
			return (ft_perror(tok.value, ": Permission denied", 1));
	if ((n == 8 || n == 12) && access(tok.value, F_OK) == -1)
		return (ft_perror(tok.value, ": No such file or directory", 1));
	if ((n == 8 || n == 12) && !access(tok.value, F_OK))
		if (access(tok.value, R_OK) == -1)
			return (ft_perror(tok.value, ": Permission denied", 1));
	return (0);
}

int			check_error_red(t_tok *prev, t_tok *toks)
{
	char	*tmp;

	if (prev->id != 14)
		tmp = 0;
	else if (ft_error_0(prev->value))
		return (1);
	else
		tmp = prev->value;
	if ((toks->id == 6 || toks->id == 9))
		if (ft_error_1(*(toks->next), toks->id, tmp))
			return (1);
	if (toks->id == 5 || toks->id == 7 || toks->id == 8
			|| toks->id == 11 || toks->id == 12)
		if (ft_error_2(*(toks->next), toks->id))
			return (1);
	if (duplicate_file(tmp, toks->id, toks->next->value, toks->next->id))
		return (1);
	return (0);
}
