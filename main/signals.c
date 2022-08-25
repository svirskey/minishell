/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:51:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 16:42:23 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	restore_prompt(int signal_type)
{
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal_type;
}

void	ctrl_c_here(int signal_type)
{
	g_sig.is_quit = 1;
	if (g_sig.is_pipe)
		exit (130);
	write(STDERR_FILENO, "\n", 1);
	(void)signal_type;
}

void	next_line(int signal_type)
{
	g_sig.is_quit = 1;
	write(STDERR_FILENO, "\n", 1);
	(void)signal_type;
}

void	back_slash(int signal_type)
{
	g_sig.is_quit = 1;
	write(STDERR_FILENO, "quit\n", 6);
	(void)signal_type;
}

void	ft_signals(t_info *info, int signal_type)
{
	if (signal_type == PROMPT)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (signal_type == HERE)
	{
		signal(SIGINT, ctrl_c_here);
		signal(SIGQUIT, SIG_IGN);
	}
	if (signal_type == EXEC)
	{
		signal(SIGINT, next_line);
		signal(SIGQUIT, back_slash);
	}
	if (signal_type == EXIT)
	{
		printf("exit\n");
		ft_free_info(info);
		exit(0);
	}
}
