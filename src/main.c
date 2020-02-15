/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:17:11 by aihya             #+#    #+#             */
/*   Updated: 2020/02/15 19:48:16 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main()
{
	aliases(TRUE);
/*	save_alias("aa", "mok");
	save_alias("aaa", "you");
	save_alias("ls", "me");
	save_alias("b", "too");
	save_alias("ab", "boom");
	printf("%s\n", get_base_name("/nam/dsjf"));
*/
//	char **args = NULL;
	// ft_chain_push(&args, "alias");
	// ft_chain_push(&args, "ls");
	// ft_chain_push(&args, "kiki=mimi");
//	ft_chain_push(&args, "kiki");
	//alias(args);
	//print_alias();
	// binaries(TRUE);
	// save_binary("ls", "/bin/ls");
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
	struct stat	st;
	int ret = stat("/Users/aihya/FOLDER/fiiile", &st);
	perror("lol");
	printf("%d %d\n", ret, st.st_mode);
//	if (st)
//		printf("EXIST\n");
//	else
//		printf("PERMISSION DENIED\n");
	return (0);
}
