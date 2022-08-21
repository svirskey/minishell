/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:55:46 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/21 13:24:56 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

int	ft_exec(t_info *info, t_list *lst)
{
	char	**cmdargs;
	char	*fpath;

	envp_update(info, ENV);
	cmdargs = create_cmd_array(lst);
	fpath = check_all_path(cmdargs, info->envp_arr);
	if (!fpath)
	{
		printf("minishell: %s: command not found\n", cmdargs[0]);
		ft_free_cmdargs(cmdargs);
		return (1);
	}
	execve(fpath, cmdargs, info->envp_arr);
	ft_free_cmdargs(cmdargs);
	perror("minishell: error in execve:");
	return (1);
}

static void	pipe_init(t_info *info, t_list *lst, int *fd)
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
	if (!(*(t_list **)(lst->key)))
		exit (0);
}

void	pipe_process(t_info *info, t_list *lst)
{
	pid_t	pid;
	int		fd[2];
	t_list	*tmp;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		pipe_init(info, lst, fd);
		tmp = info->builtins;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, (char *)(*(t_list **)(lst->key))->value))
				exit ((*(t_foo_p *)(tmp->value))(info, *(t_list **)(lst->key)));
			tmp = tmp->next;
		}
		exit(ft_exec(info, lst));
	}	
	close(fd[1]);
	waitpid(pid, &status, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (WIFEXITED(status))
		info->exit_status = WEXITSTATUS(status);
}
