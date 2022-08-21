/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:38:07 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/21 14:55:13 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	p_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
}

int	error_files(char *path, int flag)
{
	if (flag == 0)
	{
		if (access(path, F_OK))
			printf("minishell: %s: Not such file or directory.\n", path);
		else if (access(path, R_OK))
			printf("minishell: %s: Permission denied.\n", path);
	}
	else
	{
		if (access(path, F_OK))
			printf("minishell: %s: Not such file or directory.\n", path);
		else if (access(path, W_OK))
			printf("minishell: %s: Permission denied.\n", path);
	}
	return (-2);
}
