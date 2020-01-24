/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:17:11 by aihya             #+#    #+#             */
/*   Updated: 2020/01/24 20:39:57 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main()
{
	aliases(TRUE);
	save_alias("aa", "mok");
	save_alias("aaa", "you");
	save_alias("a", "me");
	save_alias("b", "too");
	save_alias("ab", "boom");
	
	binaries(TRUE);
	save_binary("ls", "/bin/ls");
	save_binary("cd", "/bin/cd");
	save_binary("man", "/bin/man");
	save_binary("cd", "/usr/bin/cd");
//	remove_binary("man");
//	unalias("a");
	print_alias();
	print_binaries();
//	printf("%s\n", is_alias("boom"));
//	printf("%s\n", is_alias("carrot"));
	return (0);
}
