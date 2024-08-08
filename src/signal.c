/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:13:49 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 16:14:33 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sig_c(int sig)
{
	g_exit_s = 1;
	ft_printf_fd(1, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	handle_sig_child(int sig)
{
	(void)sig;
	g_exit_s = 130;
}

void	handle_sig_child_sec(int sig)
{
	(void)sig;
	g_exit_s = 131;
	write(2, "Quit: 3\n", 8);
}

void	handle_sig(int which)
{
	if (which == SIG_OUT_CHILD)
	{
		signal(SIGINT, &handle_sig_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, &handle_sig_child);
		signal(SIGQUIT, &handle_sig_child_sec);
	}
}
