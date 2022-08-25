/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:38:07 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 09:51:37 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

void	p_err(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
}

void	p_err_three(char *line, char *line2, char *line3)
{
	p_err(line);
	p_err(line2);
	p_err(line3);
}

int	error_files(char *path, int flag)
{
	if (access(path, F_OK))
		p_err_three("minishell: ", path, ": No such file or directory\n");
	else if (access(path, flag))
		p_err_three("minishell: ", path, ": Permission denied\n");
	return (-2);
}

static void	file_is_missing(t_info *info, char **cmdargs)
{
	if ((ft_strncmp(cmdargs[0], "./", 2) == 0) \
	|| (ft_strncmp(cmdargs[0], "/", 1) == 0))
		p_err_three("minishell: ", cmdargs[0], ": No such file or directory\n");
	else
		p_err_three("minishell: ", cmdargs[0], ": Command not found!!!!\n");
	info->exit_status = 127;
}

void	bash_error_output(char *fpath, t_info *info, char **cmdargs)
{
	struct stat	buff;

	if (stat(fpath, &buff) == 0)
	{
		if (S_ISDIR(buff.st_mode) && ((ft_strncmp(fpath, "./", 2) == 0) \
		|| (ft_strncmp(fpath, "/", 1) == 0)))
		{
			p_err_three("minishell: ", cmdargs[0], ": This is a directory\n");
			info->exit_status = 126;
		}
		else if (S_ISREG(buff.st_mode) && access(fpath, X_OK) != 0 \
		&& ft_strncmp(fpath, "./", 2) == 0)
		{
			p_err_three("minishell: ", cmdargs[0], ": Access denied\n");
			info->exit_status = 126;
		}
		else
		{
			p_err_three("minishell: ", cmdargs[0], ": Command not found\n");
			info->exit_status = 127;
		}
	}
	else
		file_is_missing(info, cmdargs);
}
