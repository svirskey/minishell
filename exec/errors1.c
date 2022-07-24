/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:40:27 by sshana            #+#    #+#             */
/*   Updated: 2022/07/24 17:13:30 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "exec.h"

void	ft_error_pipe(void)
{
	perror("Error with pipe");
	exit(EXIT_FAILURE);
}

void	ft_error_fork(void)
{
	perror("Error with fork");
	exit(EXIT_FAILURE);
}

void	ft_error_dup(pid_t pidl, int flag)
{
	if (pidl == 0)
	{
		if (flag == 0)
			perror("Error with dup2 in child process - (Stdin)");
		else
			perror("Error with dup2 in child process - (Stdout)");
	}
	else
	{
		if (flag == 0)
			perror("Error with dup2 in parent process - (Stdin)");
		else
			perror("Error with dup2 in parent process - (Stdout)");
	}
}

void	ft_error_dup_bonus(int flaq)
{
	if (flaq == 0)
		perror("Error with dup2 (Stdin)");
	else
		perror("Error with dup2 (Stdout)");
}

void	ft_free_execve_error(char **cmdargs, int flag)
{
	if (flag == 1)
		perror("Error with path from execve");
	else if (flag == 2)
		perror("Error with calling execve");
	exit(EXIT_FAILURE);
}
