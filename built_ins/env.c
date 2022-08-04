/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:42:56 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 22:51:39 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include <stdio.h>

int ft_env(t_info *info, t_list *grammeme) 
{
	int i;

	i = 0;
	if (!info || !grammeme || !info->envp_list)
		return (1);
	envp_update(info);
	while (info->envp_arr[i])
	{
		printf("%s\n", info->envp_arr[i]);
		i++;
	}
	return 0;
}