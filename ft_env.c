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

#include "structs.h"
#include <stdio.h>

void ft_env(t_info *info) // return void ? 
{
	t_list *tmp = info->envp_list;
	while (tmp)
	{
		printf("%s=%s\n",tmp->key,tmp->value);
		tmp = tmp->next;
	}
}