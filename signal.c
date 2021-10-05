/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samin <samin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 11:31:02 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/10/05 21:41:49 by samin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig_number)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig_number == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_gloval.sig_code = 1;
		}
		else
		{
			write(1, "\n", 1);
			g_gloval.sig_code = 130;
		}
	}
	else if (sig_number == SIGQUIT && pid != -1)
	{
		write(1, "Quit: 3\n", 8);
		g_gloval.sig_code = 131;
	}
}

void	signal_initialize(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_int);
}

void	save_input_mode(void)
{
	tcgetattr(STDIN_FILENO, &g_gloval.org_term);
}

void	set_input_mode(void)
{
	tcgetattr(STDIN_FILENO, &g_gloval.new_term);
	g_gloval.new_term.c_lflag &= ECHO;
	g_gloval.new_term.c_cc[VMIN] = 1;
	g_gloval.new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_gloval.new_term);
}

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_gloval.org_term);
}
