/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:44:20 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 17:03:26 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

static void	cycle_gnl(char *limiter, int infd)
{
	char	*line;

	line = readline("here_doc> ");
	while (!g_sig.is_quit && line && ft_strcmp(line, limiter) != 1)
	{
		if (g_sig.is_quit)
			break ;
		if (line[0] == '\n')
			write(infd, "\n", 1);
		else
		{
			write(infd, line, ft_strlen(line));
			write(infd, "\n", 1);
		}
		free(line);
		if (!g_sig.is_quit)
			line = readline("here_doc> ");
		else
			break ;
	}
	if (line)
		free(line);
	close(infd);
}

int	here_doc(char *heredoc, t_info *info)
{
	int	infd;
	int	copy_in;
	int	copy_out;

	infd = open("/tmp/minishell_heredoc.txt",
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (infd == -1)
		return (-1);
	copy_in = dup(STDIN_FILENO);
	copy_out = dup(STDOUT_FILENO);
	dup2(info->std_in, STDIN_FILENO);
	dup2(info->std_out, STDOUT_FILENO);
	ft_signals(info, HERE);
	g_sig.heredoc = infd;
	cycle_gnl(heredoc, infd);
	dup2(copy_in, STDIN_FILENO);
	dup2(copy_out, STDOUT_FILENO);
	close(copy_in);
	close(copy_out);
	if (g_sig.is_quit)
		return (-2);
	infd = open("/tmp/minishell_heredoc.txt", O_RDONLY, 0777);
	return (infd);
}
