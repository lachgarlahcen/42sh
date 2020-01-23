/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:17:11 by aihya             #+#    #+#             */
/*   Updated: 2020/01/23 23:43:56 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main()
{
	aliases(TRUE);
	save_alias("a", "me");
	save_alias("aa", "mok");
	save_alias("aaa", "you");
	save_alias("b", "too");
	save_alias("bb", "boom");
	save_alias("bbb", "bim");
	
	print_hashtable(aliases(FALSE));
//	printf("%s\n", is_alias("boom"));
//	printf("%s\n", is_alias("carrot"));
	return (0);
}
