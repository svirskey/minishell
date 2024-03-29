/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:42:56 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 19:22:20 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

int	ft_env(t_info *info, t_list *grammeme)
{
	int	i;

	i = 0;
	if (!info || !grammeme || !info->envp_list)
		return (1);
	if (lst_len(grammeme) > 1)
	{
		p_err("minishell: env: too many arguments\n");
		return (1);
	}
	envp_update(info, ENV);
	while (info->envp_arr[i])
	{
		printf("%s\n", info->envp_arr[i]);
		i++;
	}
	return (0);
}
