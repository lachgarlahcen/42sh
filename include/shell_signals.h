/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 05:27:56 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 19:07:45 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_SIGNALS_H
# define SHELL_SIGNALS_H

# include "shell.h"
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>

void	signals(int c);

#endif
