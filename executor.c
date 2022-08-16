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
	cmdargs = create_cmd_array(lst);
	fpath = check_all_path(cmdargs, info->envp_arr);
	if (!fpath)
	{
		write(STDERR_FILENO, "minishell: execve: Error with command\n", 39);
		ft_free_cmdargs(cmdargs);
		return (1);
	}
	execve(fpath, cmdargs, info->envp_arr);
	ft_free_cmdargs(cmdargs);
	return (0);
}

static void	pipe_process(t_info *info, t_list *lst)
{
	pid_t	pid;
	int		fd[2];
	t_list	*tmp;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		info->fd_in = check_infile(lst, info);
		info->fd_out = check_outfile(lst);
		if (info->fd_in == -2 || info->fd_out == -2)
			exit (1);
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
		else if (lst->next)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		tmp = info->builtins;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, (char *)(*(t_list **)(lst->key))->value))
				exit ((*(t_foo_p *)(tmp->value))(info, *(t_list **)(lst->key)));
			tmp = tmp->next;
		}
		exit(ft_exec(info, lst));
	}
	else
	{		
		close(fd[1]);
		waitpid(pid, &status, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (WIFEXITED(status))
			info->exit_status = WEXITSTATUS(status);
	}
}

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

static int	single_process(t_info *info)
{
	t_list	*tmp;

	info->fd_in = check_infile(info->grammemes, info);
	info->fd_out = check_outfile(info->grammemes);
	if (info->fd_in == -2 || info->fd_out == -2)
	{
		if (info->fd_in > - 1)
			close(info->fd_in);
		if (info->fd_out > - 1)
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
	tmp = info->builtins;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, (char *)(*(t_list **)(info->grammemes->key))->value))
		{
			info->exit_status = (*(t_foo_p *)(tmp->value))(info, *(t_list **)(info->grammemes->key));
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
