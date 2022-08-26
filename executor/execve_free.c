/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:31:09 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 17:31:31 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_cmdargs(char **cmdargs)
{
	int	i;

	i = 0;
	if (!cmdargs)
		return ;
	while (cmdargs[i])
	{
		free(cmdargs[i]);
		i++;
	}
	free(cmdargs);
}
