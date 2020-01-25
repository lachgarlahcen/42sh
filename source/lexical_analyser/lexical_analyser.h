/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 06:13:39 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 23:59:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALAYSER_H
# define LEXICAL_ANALAYSER_H
# include "../my_shell.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_tok
{
	int				id;
	char			*tok;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_env
{
	char	*line;
	t_tok	*tokens;
}				t_env;

int				init_environ(void);
void			free_environ(int status);
t_env			*save_environ(t_env **environ);
void			add_to_environ(char *line, t_tok *tokens);

int				g_check(int check, int init);

char			*line_editing(char *str);
int				syntax_analyser(char *str);
int				save_tokens(t_tok **t, char *token);
int				save_alias_tokens(char *al, t_tok **t, char *tmp);

int				end_inhibitors(char **s, int p, char ch);
int				free_perror(char *s1, char *s2, int check, int r);
char			*strjoin_free(char *s1, char *s2, int f1, int f2);

void			free_toks(t_tok *toks);

int				isdelim(char ch);
int				isinhib(char ch);
int				isnumber(char *str);

int				lexical_analyser(void);

char			*check_alias(char *al); /* call this */

#endif
