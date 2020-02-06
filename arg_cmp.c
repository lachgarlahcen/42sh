/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 04:58:33 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/06 01:06:06 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int     test_string_eq(char **argv)
{
        /* we should do parsing against the erros 
ex :    test =hello
        test world =

*/
    return(!ft_strequ(argv[1], argv[3]));   
}

int     test_string_neq(char **argv)
{
    return(ft_strequ(argv[1], argv[3]));   
}

int     test_int_eq(char **argv)
{
    int i;
    int j;
    
    i = 0;
    j = 1;
    while(argv[j][i])
    {
        if (!ft_isdigit(argv[j][i]))
        {
            ft_putendl_fd("integer expression expected",2);
            return(2);
        }
        i++;
        if (j != 3 && !argv[j][i])
        {
            j = 3;
            i = 0;            
        }
    }
    i = ft_atoi(argv[1]);
    j = ft_atoi(argv[3]);
    return(!(i == j));
}

int     test_int_ne(char **argv)
{
    int i;
    int j;
    
    i = 0;
    j = 1;
    while(argv[j][i])
    {
        if (!ft_isdigit(argv[j][i]))
        {
            ft_putendl_fd("integer expression expected",2);
            return(2);
        }
        i++;
        if (j != 3 && !argv[j][i])
        {
            j = 3;
            i = 0;            
        }
    }
    return (!test_int_eq(argv));
}

int     test_int_ge(char **argv)
{
    int i;
    int j;
    i = 0;
    j = 1;
    while(argv[j][i])
    {
        if (!ft_isdigit(argv[j][i]))
        {
            ft_putendl_fd("integer expression expected",2);
            return(2);
        }
        i++;
        if (j != 3 && !argv[j][i])
        {
            j = 3;
            i = 0;            
        }
    }
    i = ft_atoi(argv[1]);
    j = ft_atoi(argv[3]);
    return (!(i >= j));
}

int     test_int_lt(char **argv)
{
    int i;
    int j;
    i = 0;
    j = 1;
    while(argv[j][i])
    {
        if (!ft_isdigit(argv[j][i]))
        {
            ft_putendl_fd("integer expression expected",2);
            return(2);
        }
        i++;
        if (j != 3 && !argv[j][i])
        {
            j = 3;
            i = 0;            
        }
    }
    i = ft_atoi(argv[1]);
    j = ft_atoi(argv[3]);
    return (!(i < j));
}

int     test_int_le(char **argv)
{
    int i;
    int j;
    
    i = 0;
    j = 1;
    while(argv[j][i])
    {
        if (!ft_isdigit(argv[j][i]))
        {
            ft_putendl_fd("integer expression expected",2);
            return(2);
        }
        i++;
        if (j != 3 && !argv[j][i])
        {
            j = 3;
            i = 0;            
        }
    }
    j = ft_atoi(argv[1]);
    j = ft_atoi(argv[3]);
    return (!(i <= j));
}

int     test_cmp(char **argv)
{
    int i;

    t_cmp operator[] = {
        {"=",&test_string_eq},
        {"!=",&test_string_neq},
        {"-eq",&test_int_eq},
        {"-ne",&test_int_ne},
        {"-ge",&test_int_ge},
        {"-lt",&test_int_lt},
        {"-le",&test_int_le}
    };
    i = 0;
    while(i < sizeof(operator)/sizeof(*operator))
    {
        if (ft_strequ(argv[2],operator[i].operator))
            return(operator[i].f(argv));
        i++;
    }
    ft_putendl_fd("operator not found",2);
    return(2);
}