/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:44:20 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 17:56:59 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static void	cycle_gnl(char *limiter, int infd)
{
	char	*line;

	line = readline("here_doc> ");
	while (ft_strcmp(line, limiter) != 1)
	{
		if (line[0] == '\n')
			write(infd, "\n", STDOUT_FILENO);
		else
		{
			write(infd, line, ft_strlen(line));
			write(infd, "\n", STDOUT_FILENO);
		}
		free(line);
		line = readline("here_doc> ");
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
	cycle_gnl(heredoc, infd);
	dup2(copy_in, STDIN_FILENO);
	dup2(copy_out, STDOUT_FILENO);
	close(copy_in);
	close(copy_out);
	infd = open("/tmp/minishell_heredoc.txt", O_RDONLY, 0777);
	return (infd);
}
