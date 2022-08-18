/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:15:18 by sshana            #+#    #+#             */
/*   Updated: 2022/08/18 20:36:36 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	cycle_gnl(char *limiter, int infd)
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

static int	here_doc(char *heredoc, t_info *info)
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

int	check_infile(t_list *lst, t_info *info)
{
	int		infd;
	t_list	*tmp;

	tmp = *(t_list **)lst->value;
	infd = -1;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "read") == 1)
		{
			if (infd > -1)
				close(infd);
			infd = open((char *)tmp->value, O_RDONLY, 0777);
			if (infd == -1)
			{
				print_error("minishell: ");
				print_error((char *)tmp->value);
				print_error(": Cannot open file or directory.\n");
				return (-2);
			}
		}
		else if (ft_strcmp(tmp->key, "heredoc") == 1)
		{
			if (infd > -1)
				close(infd);
			infd = here_doc((char *)tmp->value, info);
			if (infd == -1)
			{
				print_error("minishell: Error with open tmp files (heredoc).\n");
				return (-2);
			}
		}
		tmp = tmp->next;
	}
	return (infd);
}

int	check_outfile(t_list *lst)
{
	t_list	*tmp;
	int		outfd;

	tmp = *(t_list **)lst->value;
	outfd = -1;
	while (tmp)
	{
		if ((ft_strcmp(tmp->key, "write") == 1) || (ft_strcmp(tmp->key, "append") == 1))
		{
			if (outfd != -1)
				close(outfd);
			if (ft_strcmp(tmp->key, "write") == 1)
				outfd = open((char *)tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			else if (ft_strcmp(tmp->key, "append") == 1)
				outfd = open((char *)tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (outfd == -1)
			{
				print_error("minishell: Error with output file.\n");
				return (-2);
			}
		}
		tmp = tmp->next;
	}
	return (outfd);
}
