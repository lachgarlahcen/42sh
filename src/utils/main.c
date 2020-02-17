/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:17:11 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 23:14:20 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main()
{
	aliases(TRUE);
	save_alias("aa", "mok");
	save_alias("aaa", "you");
	save_alias("ls", "me");
//	save_alias("b", "too");
//	save_alias("ab", "boom");

	binaries(TRUE);
	save_binary("ls", "/bin/ls");
	save_binary("ls", "/bin/ls");
	save_binary("ls", "/bin/ls");
	char **args = NULL;
	ft_chain_push(&args, "hash");
//	ft_chain_push(&args, "-r");
//	ft_chain_push(&args, "ls");
//	ft_chain_push(&args, "mimi");
//	ft_chain_push(&args, "cat");
	hash(args);
	ft_chain_free(&args);
	printf("---------\n");
	ft_chain_push(&args, "hash");
	hash(args);

	//print_alias();
	
	// save_binary("cd", "/bin/cd");
	// save_binary("man", "/bin/man");
	// save_binary("cd", "/usr/bin/cd");
//	remove_binary("man");
//	unalias("a");
//	print_alias();
//	print_binaries();
//	printf("%s\n", is_alias("boom"));
//	printf("%s\n", is_alias("carrot"));

//	type(binaries_names(FALSE));
//	if (st)
//		printf("EXIST\n");
//	else
//		printf("PERMISSION DENIED\n");
	return (0);
}
