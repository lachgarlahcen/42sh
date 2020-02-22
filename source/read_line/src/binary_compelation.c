/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_compelation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 06:21:33 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/22 15:41:09 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static void free_2d_str(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        free(str[i]);
        i++;
    }
    free(str[i]);
    free(str);
}

static int fill_matches(char *folder, char *match, t_data **matches)
{
    DIR *dir;
    struct dirent *content;
    int count;
    char *path;
    struct stat sb;

    count = 0;
    dir = opendir(folder);
    if (!dir)
        return (0);
    while ((content = readdir(dir)) != NULL)
    {
        if (content->d_type == DT_DIR)
            continue;
        path = ft_strjoin_f(ft_strjoin(folder, "/"), content->d_name, 1, 0);
        if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
        {
            if (match[0] != 0 && !ft_memcmp(match, content->d_name, ft_strlen(match)))
            {
                add_new_match(matches, content);
                count++;
            }
            else if (match[0] == 0)
            {
                add_new_match(matches, content);
                count++;
            }
        }
        free(path);
    }
    closedir(dir);
    return (count);
}

int fill_aliases(char *match, t_data **matches)
{
    char **tab;
    int res;
    int i;
    t_data *new_match;

    tab = aliases_names(0);
    res = 0;
    if (!tab)
        return (res);
    i = 0;
    while (tab[i])
    {
        if (!ft_memcmp(match, tab[i], ft_strlen(match)))
            {
                new_match = new_node(ft_strdup(tab[i]));
                sortedisert(matches, new_match);
                res++;
            }
        i++;
    }
    return (res);
}
void binary_compelation(char *match, t_cmd *l)
{
    char *path;
    t_data *matches;
    char **tab;
    int count;
    int i;

    count = 0;
    i = -1;
    path = get_variable("PATH");
    matches = NULL;
    if (path)
    {
        tab = ft_strsplit(path, ':');
        while (tab[++i])
            count += fill_matches(tab[i], match, &matches);
        ft_strdel(&path);
        free_2d_str(tab);
    }
    count += fill_aliases(match, &matches);
    complete_or_print(matches, l, count, match);
    free_data(&matches);
}