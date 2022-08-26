/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:43:39 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:45:38 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

void	malloc_err(void)
{
	p_err("minishell: error with malloc\n");
	exit (1);
}
