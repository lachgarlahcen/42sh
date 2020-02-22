/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 04:47:14 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/22 21:47:08 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

#define CHECK_PATH_CONTEXT(patt) (ft_strrchr(patt, '/') || !ft_strcmp(patt, "..") || !ft_strcmp(patt, "."))
#define IS_BEGIN_CMD(c) (c == ';' || c == '|' || c == '&')
enum context
{
    BINARY,
    VARS,
    PATH
};

int ft_countwords(char *str, int c)
{
    int words;
    int i;

    words = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] != c && str[i])
        {
            while (str[i] != c && str[i])
                i++;
            words++;
        }
        while (str[i] == c)
            i++;
    }
    return (words);
}
/*
** check word count from 0 or one of cmds seperators {;, |, &}
** but if there is / that means thats a path 
** w_c is word count
** if the cmd is like : {ls |        l<TAB>} or {      <TAB>} or {l<TAB>}
*/
int check_binary_context(char *str, int pos)
{
    int i;
    int w_c;

    if (pos == 0)
        return (1);
    i = pos - 1;
    while (i >= 0)
    {
        if (str[i] == '/')
            return (0);
        else if (IS_BEGIN_CMD(str[i]))
            break;
        i--;
    }
    w_c = ft_countwords(&str[i + 1], ' ');
    if (w_c == 0 || (w_c == 1 && str[pos - 1] != ' '))
        return (1);
    return (0);
}
int check_vars_context(char *word)
{
    if (!word)
        return (0);
    if (word[0] == '$' && !ft_strrchr(word, ';') && !ft_strrchr(word, '|') &&
        !ft_strrchr(word, '&'))
        return (1);
    return (0);
}

char *get_last_word_path(char *patt, int pos)
{
    int i;

    if (!patt)
        return (NULL);
    i = pos - 1;
    while (i >= 0)
    {
        if (IS_BEGIN_CMD(patt[i]) || patt[i] == ' ')
            break;
        i--;
    }
    return (ft_strdup(&patt[i + 1]));
}
/*
** get context to get were to look up for the pattern
*/
int get_context(char *patt, int pos, char *patt_l_d)
{
    if (check_vars_context(patt_l_d))
        return (VARS);
    if (check_binary_context(patt, pos))
        return (BINARY);
    return (PATH);
}
/*
** this function is excuted when the TAB is typed
** first get pattern 
** the pattern is the word before 
*/
void completion(t_cmd *l)
{
    char *pattern;
    int context;
    char *last_word;

    pattern = ft_strsub(l->chars, 0, l->cur);
    last_word = get_last_word_path(pattern, l->cur);
    context = get_context(pattern, l->cur, last_word);
    free(pattern);
    if (context == PATH)
        path_completion(last_word, l);
    else if (context == VARS)
       vars_compelation(last_word, l);
    else
       binary_compelation(last_word, l);
    ft_strdel(&last_word);
}