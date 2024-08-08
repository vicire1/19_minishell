/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:13:49 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:18:36 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sig_c(int sig)
{
	(void)sig;
	g_exit_s = 1;
	ft_printf_fd(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig(void)
{
	signal(SIGINT, &handle_sig_c);
	signal(SIGQUIT, SIG_IGN);
}
