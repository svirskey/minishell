/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 08:25:56 by sshana            #+#    #+#             */
/*   Updated: 2022/08/11 09:43:18 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static int	ft_exec(t_info *info, t_list *lst)
{
	char	**cmdargs;
	char	*fpath;

    envp_update(info);
	cmdargs = make_massive_command(info, lst);
    fpath = check_all_path(cmdargs, info->envp_arr);
	if (!fpath)
	{
		ft_free_cmdargs(cmdargs);
		return (-1);
	}
	execve(fpath, cmdargs, info->envp_arr);
	ft_free_cmdargs(cmdargs);
	return (1);
}

static void	child_process(t_info *info, t_list *lst)
{
	pid_t	pid;
	int		fd[2];
	int		infd;
	int		outfd;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		infd = check_infile(info, lst);
		outfd = check_outfile(info, lst);
		close(fd[0]);
		if (infd > -1)
		{
			dup2(infd, STDIN_FILENO);
			close(infd);
		}
		if (outfd != -1)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		else
			dup2(fd[1], 1);
		close(fd[1]);
		//if (check_built_in(str, line) == 1)
		//	exit (0);
		if (ft_exec(info, lst) == -1)
			exit(0);
		perror("Child process.\n");
		exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

static void	parent_process(t_info *info, t_list *lst)
{
	int	infd;
	int	outfd;

	infd = check_infile(info, lst);
	outfd = check_outfile(info, lst);
	if (infd > -1)
    {
    	dup2(infd, STDIN_FILENO);
    	close(infd);
    }
	//if (check_built_in(str, line) == 1)
	//	exit (0);
	if (outfd != -1)
	{
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	if (ft_exec(info, lst) == -1)
		exit(0);
    perror("Parent.\n");
	exit(1);
}

static void	clean_dup_redir(t_info *str, int in_std, int out_std)
{
	t_info *tmp;

	tmp = str;
	if (tmp->redir_in != -1)
	{
		dup2(in_std, 0);
		close(tmp->redir_in);
		tmp->redir_in = -1;
	}
	if (tmp->redir_out != -1)
	{
		dup2(out_std, 1);
		close(tmp->redir_out);
		tmp->redir_out = -1;
	}
}

static int	redir_dup(t_info *str, int flag)
{
	int	fd;

    fd = dup(flag);
    close(flag);
	if (flag == 0)
		dup2(str->redir_in, flag);
	else (flag == 1)
		dup2(str->redir_out, flag);
    return (fd);
}

static void	close_redir(t_info *info)
{
	if (info->redir_in != -1)
	{
		close(info->redir_in);
		info->redir_in = -1;
	}
	if (info->redir_out != -1)
	{
		close(info->redir_out);
		info->redir_out = -1;
	}
}

static int	one_not_builin_process(t_info *info, t_list *lst)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
        close(fd[0]);
		info->redir_in = check_infile(info, lst);
		if (info->redir_in != -1)
			dup2(info->redir_in, STDIN_FILENO);
		info->redir_out = check_outfile(info, lst);
		if (info->redir_out != -1)
			dup2(info->redir_out, STDOUT_FILENO);
		close_redir(info);
		ft_exec(info, lst);
        perror("ERROR with one command.\n");
        exit(1);
    }
	close(fd[1]);
    close(fd[0]);
	waitpid(pid, NULL, 0);
	return (0);
}

static int	one_process(t_info *info)
{
	int		in_std;
	int		out_std;

    info->redir_in = check_infile(info, info->grammemes);
	info->redir_out = check_outfile(info, info->grammemes);
	if (info->redir_in != -1)
		in_std = redir_dup(info, 0);
	if (info->redir_out != -1)
		out_std = redir_dup(info, 1);
	///if (check_built_in(str, line) == 1)	///and do built-in if he is there
	//{
	//	clean_dup_redir(str, in_std, out_std);
	//	return (0);
	//}
	clean_dup_redir(info, in_std, out_std);
	one_not_builin_process(info, info->grammemes);
	return (0);
}

static void    pipe_process(t_info *info, int pipe_count)
{
    pid_t   pid0;
    int     fd[2];
    t_list *lst;

    lst = info->grammemes;
    pipe(fd);
    pid0 = fork();
    if (pid0 == 0)
    {
        close(fd[0]);
        close(fd[1]);
        while (pipe_count > 0)
        {
            child_process(info, lst);
            pipe_count--;
            lst = lst->next;
        }
        parent_process(info, lst);
    }
    close(fd[1]);
    close(fd[0]);
    waitpid(pid0, NULL, 0);
}

void executor(t_info *info)
{
	int	pipe_count;

	pipe_count = lst_len(info->grammemes) - 1;
	if (pipe_count == 0)
		one_process(info);
	else
		pipe_process(info, pipe_count);
}