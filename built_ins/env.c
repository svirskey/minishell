/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:42:56 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 21:50:37 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include <stdio.h>

int ft_env(t_info *info) 
{
	t_list *tmp;

	if (!info || !info->envp_list)
		return (1);
	tmp = info->envp_list;
	while (tmp)
	{
		printf("%s=%s\n",(char *)tmp->key,(char *)tmp->value);
		tmp = tmp->next;
	}
	return 0;
}