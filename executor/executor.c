/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 08:25:56 by sshana            #+#    #+#             */
/*   Updated: 2022/08/21 15:18:22 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "libft_funcs.h"

static void	execve_process(t_info *info, t_list *lst)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(ft_exec(info, lst));
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			info->exit_status = WEXITSTATUS(status);
	}
}

static int	single_init(t_info *info)
{
	info->fd_in = check_infile(info->grammemes, info);
	info->fd_out = check_outfile(info->grammemes, info);
	if (info->fd_in == -2 || info->fd_out == -2)
	{
		if (info->fd_in > -1)
			close(info->fd_in);
		if (info->fd_out > -1)
			close(info->fd_out);
		info->exit_status = 1;
		return (info->exit_status);
	}
	if (info->fd_in > -1)
	{
		dup2(info->fd_in, STDIN_FILENO);
		close(info->fd_in);
	}
	if (info->fd_out > -1)
	{
		dup2(info->fd_out, STDOUT_FILENO);
		close(info->fd_out);
	}
	return (0);
}

static int	single_process(t_info *info)
{
	t_list	*tmp;

	if (single_init(info))
		return (info->exit_status);
	if (!(*(t_list **)(info->grammemes->key)))
		return (0);
	tmp = info->builtins;
	while (tmp)
	{
		if (ft_strcmp(tmp->key,
				(char *)(*(t_list **)(info->grammemes->key))->value))
		{
			info->exit_status = (*(t_foo_p *)(tmp->value))(info,
					*(t_list **)(info->grammemes->key));
			return (info->exit_status);
		}
		tmp = tmp->next;
	}
	execve_process(info, info->grammemes);
	return (0);
}

void	executor(t_info *info)
{
	t_list	*lst;

	lst = info->grammemes;
	ft_signals(info, EXEC);
	if (lst_len(lst) == 1)
		single_process(info);
	else
	{
		while (lst)
		{
			pipe_process(info, lst);
			lst = lst->next;
		}
	}
	dup2(info->std_in, STDIN_FILENO);
	dup2(info->std_out, STDOUT_FILENO);
}
