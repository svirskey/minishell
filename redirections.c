/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:15:18 by sshana            #+#    #+#             */
/*   Updated: 2022/08/21 14:11:34 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	check_infd(t_info *info, t_list *tmp, int *infd)
{
	if (ft_strcmp(tmp->key, "read") == 1)
	{
		if ((*infd) > -1)
			close(*infd);
		*infd = open((char *)tmp->value, O_RDONLY, 0777);
		if ((*infd) == -1)
		{
			p_error("minishell: ");
			p_error((char *)tmp->value);
			p_error(": Cannot open file or directory.\n");
			return (-2);
		}
	}
	else if (ft_strcmp(tmp->key, "heredoc") == 1)
	{
		if ((*infd) > -1)
			close(*infd);
		*infd = here_doc((char *)tmp->value, info);
		if ((*infd) == -1)
		{
			perror("minishell:");
			return (-2);
		}
	}
	return (0);
}

int	check_infile(t_list *lst, t_info *info)
{
	int		infd;
	t_list	*tmp;

	tmp = *(t_list **)lst->value;
	infd = -1;
	while (tmp)
	{
		if (check_infd(info, tmp, &infd) == -2)
			return (-2);
		tmp = tmp->next;
	}
	return (infd);
}

static void	opn_fd(int *outfd, t_list *tmp)
{
	if ((*outfd) != -1)
		close(*outfd);
	if (ft_strcmp(tmp->key, "write") == 1)
		*outfd = open((char *)tmp->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (ft_strcmp(tmp->key, "append") == 1)
		*outfd = open((char *)tmp->value,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
}

int	check_outfile(t_list *lst)
{
	t_list	*tmp;
	int		outfd;

	tmp = *(t_list **)lst->value;
	outfd = -1;
	while (tmp)
	{
		if ((ft_strcmp(tmp->key, "write") == 1)
			|| (ft_strcmp(tmp->key, "append") == 1))
		{
			opn_fd(&outfd, tmp);
			if (outfd == -1)
			{
				printf("minishell: %s: Permission denied\n", (char *)tmp->value);
				return (-2);
			}
		}
		tmp = tmp->next;
	}
	return (outfd);
}
