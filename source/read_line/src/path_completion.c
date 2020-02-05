/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 08:12:04 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 04:00:54 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char *get_base(char *path, int len)
{
    int i;

    i = len;
    while (--i >= 0)
        if (path[i] == '/')
            break;
    return (ft_strsub(path, 0, i + 1));
}

void get_folder_start(char *patt, char **folder, char **start, int pos)
{
    char *slash;

    if ((slash = ft_strrchr(patt, '/')))
    {
        *start = ft_strdup(slash + 1);
        *folder = get_base(patt, pos);
    }
    else
    {
        *folder = ft_strdup(".");
        *start = ft_strdup(patt);
    }
}
char *add_new_match(t_data **matches, struct dirent *content)
{
    t_data *new_match;
    char *data;

    if (content->d_type == DT_DIR)
        data = ft_strjoin(content->d_name, "/");
    else
        data = ft_strdup(content->d_name);

    new_match = new_node(data);
    sortedisert(matches, new_match);
    return (data);
}

int fill_matches(char *folder, char *match, t_data **matches, t_cmd *l)
{
    DIR *dir;
    struct dirent *content;
    int count;
    int len;

    count = 0;
    l->max_m = 0;
    dir = opendir(folder);
    if (!dir)
        return (0);
    while ((content = readdir(dir)) != NULL)
    {
        if (match[0] != 0 && !ft_memcmp(match, content->d_name, ft_strlen(match)))
        {
            len = ft_strlen(add_new_match(matches, content));
            if (l->max_m < len)
                l->max_m = len;
            count++;
        }
        if (match[0] == 0 && ft_memcmp(content->d_name, "..", 2) && ft_memcmp(content->d_name, ".", 1))
        {
            len = ft_strlen(add_new_match(matches, content));
            if (l->max_m < len)
                l->max_m = len;
            count++;
        }
    }
    closedir(dir);
    return (count);
}

/*
** complete_or_print: if the number of matches is more than one then print it so the user see it
** else if number is just one complet the cmd 
** but if the number is 0 nothing to do
*/
void complete_or_print(t_data *matches, t_cmd *l, int count, char *match)
{
    int i;
    if (!count)
        return;
    i = ft_strlen(match);
    if (count == 1)
    {
        while (matches->data[i])
        {
            l->key = matches->data[i];
            add_at(l);
            i++;
        }
    }
    else
        print_matches(matches, l, count, match);
}
/*
** get all file that looks like the pattern 
** the patt will be spliiten to 2 parts 
** first part is the base path 
** the second is the pattern if there is one 
*/
void path_completion(char *patt, t_cmd *l)
{
    char *folder;
    char *start_with;
    t_data *matches;
    int count;

    folder = NULL;
    start_with = NULL;
    matches = NULL;
    get_folder_start(patt, &folder, &start_with, l->cur);
    count = fill_matches(folder, start_with, &matches, l);
    complete_or_print(matches, l, count, start_with);
    free(start_with);
    free(folder);
    free_data(&matches);
}