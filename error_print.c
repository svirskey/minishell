/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:38:07 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/21 15:16:05 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

void	p_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
}

void	p_err_three(char *line, char *line2, char *line3)
{
	p_error(line);
	p_error(line2);
	p_error(line3);
}

int	error_files(char *path, int flag)
{
	if (access(path, F_OK))
		p_err_three("minishell: ", path, ": No such file or directory\n");
	else if (access(path, flag))
		p_err_three("minishell: ", path, ": Permission denied\n");
	return (-2);
}
