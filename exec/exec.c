/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:35:48 by sshana            #+#    #+#             */
/*   Updated: 2022/07/24 18:59:04 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_free_paths_from_envp(char **paths_from_envp)
{
	int	i;

	i = 0;
	while (paths_from_envp[i] != 0)
	{
		free(paths_from_envp[i]);
		i++;
	}
	free(paths_from_envp);
}

char	*ft_check_access(char **paths_from_envp, char *cmdargs)
{
	int		i;
	char	*path;
	char	*one_path;

	i = 0;
	while (paths_from_envp[i] != 0)
	{
		one_path = ft_strjoin(paths_from_envp[i], "/");
		path = ft_strjoin(one_path, cmdargs);
		free(one_path);
		if (access(path, F_OK) == 0)
		{
			ft_free_paths_from_envp(paths_from_envp);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_paths_from_envp(paths_from_envp);
	return (0);
}

char	*check_all_path(char *cmdargs, char **envp)
{
	char	*path;
	char	**paths_from_envp;
	char	*path_string;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	path_string = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!path_string)
		return (0);
	paths_from_envp = ft_split(path_string, ':');
	free(path_string);
	if (!paths_from_envp)
		return (0);
	path = ft_check_access(paths_from_envp, cmdargs);
	if (!path)
		return (0);
	return (path);
}

void	ft_exec(void *path, void *argv, char **envp)
{
	char	**cmdargs;
	char	*fpath;
	
	cmdargs = ft_split(argv, ' ');
	fpath = check_all_path(cmdargs[0], envp);

	//execve(fpath, cmdargs, envp);
	execve(path, cmdargs, envp);
	ft_free_execve_error(cmdargs, 2);	//принудительный exit
}

void	child_process_bonus(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	if (pipe(fd) == -1)
		ft_error_pipe();
	pid = fork();
	if (pid == -1)
		ft_error_fork();
	if (pid == 0)
	{
		printf("Child\n");            //контроль за правильным выполнением (сначала дочка, потом дуб на чтение/ потом родитель) //потом убрать
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)		//Настроить fd
			ft_error_dup(pid, 1);
		ft_exec("/bin/ls", "ls -l", envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		printf("Parent intermediate\n");          //контроль за правильным выполнением (сначала дочка, потом дуб на чтение/ потом родитель) //потом убрать
		if (dup2(fd[0], STDIN_FILENO) == -1)		//Настроить fd
			ft_error_dup(pid, 0);
	}
}

void	parent_process_bonus(int argc, char **argv, char **envp)
{
	printf("Parent end\n");               //контроль за правильным выполнением (сначала дочка, потом дуб на чтение/ потом родитель) //потом убрать
	if (dup2(1, STDOUT_FILENO) == -1)   		//Настроить fd
	{
		close(1);
		ft_error_dup_bonus(1);
	}
	ft_exec("/bin/wc", "wc -l", envp);
}

int executer(int argc, char **argv, char **envp)
{
	int i;

	//if (built_in)
		//			check - if command only built-in - execute function built-in[7]
	//else
	i = 0;
    while (i < 1) 
	{
        child_process_bonus(argc, argv, envp);		//argv - command
		i++;
	}
    parent_process_bonus(argc, argv, envp);			//argv - command
}

int main(int argc, char **argv, char **envp)
{
	executer(argc, argv, envp);
	return (0);
}