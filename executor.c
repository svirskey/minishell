/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 08:25:56 by sshana            #+#    #+#             */
/*   Updated: 2022/08/12 20:09:58 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static int	ft_exec(t_info *info, t_list *lst)
{
	char	**cmdargs;
	char	*fpath;

    envp_update(info);
	cmdargs = make_massive_command(lst);
    fpath = check_all_path(cmdargs, info->envp_arr);
	if (!fpath)
	{
		perror("Error with path!");
		ft_free_cmdargs(cmdargs);
		return (-1);
	}
	execve(fpath, cmdargs, info->envp_arr);
	ft_free_cmdargs(cmdargs);
	return (1);
}

static void	pipe_process(t_info *info, t_list *lst)
{
	pid_t	pid;
	int		fd[2];
	t_list	*tmp;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		info->fd_in = check_infile(lst, info);
		info->fd_out = check_outfile(lst);
		if (info->fd_in > -1)
		{
			dup2(info->fd_in, STDIN_FILENO);
			close(info->fd_in);
		}
		if (info->fd_out > -1)
		{
			perror("fd > -1");
			dup2(info->fd_out, STDOUT_FILENO);
			close(info->fd_out);
		}
		else if (lst->next)
		{
			perror("lst->next");
			dup2(fd[1], STDOUT_FILENO);
		}
		close(fd[1]);
		tmp = info->builtins;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, (char *)(*(t_list **)(info->grammemes->key))->value))
			{
				info->exit_status = (*(t_foo_p *)(tmp->value))(info, *(t_list **)(info->grammemes->key));
				exit(info->exit_status);
			}
			tmp = tmp->next;
		}
		if (ft_exec(info, lst) == -1)
			exit(1);
		exit(0);
	}
	else
	{		
		close(fd[1]);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	execve_process(t_info *info, t_list *lst)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		info->fd_in = check_infile(info->grammemes, info);
		info->fd_out = check_outfile(info->grammemes);
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
		ft_exec(info, lst);
        perror("ERROR with one command.\n");
        exit(1);
    }
	waitpid(pid, NULL, 0);
}

static int	single_process(t_info *info)
{
	t_list *tmp;

	tmp = info->builtins;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, (char *)(*(t_list **)(info->grammemes->key))->value))
		{
		 	info->fd_in = check_infile(info->grammemes, info);
			info->fd_out = check_outfile(info->grammemes);
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
			info->exit_status = (*(t_foo_p *)(tmp->value))(info, *(t_list **)(info->grammemes->key));
			if (info->fd_in > -1)
				dup2(info->std_in, STDIN_FILENO);
			if (info->fd_out > -1)
				dup2(info->std_out, STDOUT_FILENO);
			return (0);
		}
		tmp = tmp->next;
	}
	execve_process(info, info->grammemes);
	return (0);
}

void executor(t_info *info)
{
    t_list *lst;

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
