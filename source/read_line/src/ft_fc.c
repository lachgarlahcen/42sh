/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:35:13 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 00:47:57 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#define IS_OPT(cmd) (cmd[0] == '-' && (cmd[1] != '\0' || cmd[1] != '-'))
#define FC_USAGE "fc: usage: fc [-e ename] [-nlrs] [first] [last]\n"
#define FC_EDITOR_ERR "42sh: fc: -e: option requires an argument\n"

static int		ft_get_flags(char *opt, t_fc *fc)
{
	int i;

	i = -1;
	while (opt[++i])
	{
		if (opt[i] == 'l')
			fc->l = 1;
		else if (opt[i] == 's')
			fc->s = 1;
		else if (opt[i] == 'r')
			fc->r = 1;
		else if (opt[i] == 'n')
			fc->n = 1;
		else if (opt[i] == 'e')
			return (2);
		else if (opt[i] != '-')
		{
			ft_putstr_fd("42sh: fc: Invalid Option ", 2);
			ft_putchar_fd(opt[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd(FC_USAGE, 2);
			return (0);
		}
	}
	return (1);
}

static int		ft_fc_get_flags(char **av, t_fc *fc)
{
	int i;
	int j;

	i = 0;
	while (av[++i])
		if (IS_OPT(av[i]) && !ft_atoi(av[i]))
		{
			if ((j = ft_get_flags(av[i], fc)) == 0)
				return (0);
			else if (j == 2)
			{
				if (av[i + 1] == NULL)
					return (ft_putstr_err_ret(FC_EDITOR_ERR, 0));
				else
					fc->editor = ft_strdup(av[++i]);
			}
		}
		else
		{
			fc->first = ft_strdup(av[i]);
			if (av[i + 1] != NULL)
				fc->last = ft_strdup(av[i + 1]);
			break ;
		}
	return (1);
}

void			ft_init_fc(t_fc *fc)
{
	fc->e = 0;
	fc->l = 0;
	fc->n = 0;
	fc->r = 0;
	fc->s = 0;
	fc->editor = NULL;
	fc->first = NULL;
	fc->last = NULL;
}

int				ft_free_fc(t_fc *fc)
{
	if (fc->editor)
		free(fc->editor);
	if (fc->first)
		free(fc->first);
	if (fc->last)
		free(fc->last);
	return (0);
}

int				ft_fc(char **av)
{
	t_fc	fc;
	int		res;

	if (getpid() != g_shell_pgid)
	{
		ft_putendl_fd("42sh: fc: No fc In child proccess", 2);
		return (1);
	}
	ft_init_fc(&fc);
	if (!ft_fc_get_flags(av, &fc))
		return (ft_free_fc(&fc));
	if (fc.s)
		res = ft_fc_redo(&fc);
	else if (fc.l)
		res = ft_fc_list(&fc);
	else
		res = ft_fc_editor(&fc);
	ft_free_fc(&fc);
	return (res);
}
