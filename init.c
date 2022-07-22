/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:17:28 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 21:38:15 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

void	env_init(t_info *info, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*key;
	char	*value;
	
	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] != '=')
			j++;
		key = malloc(j + 1);
		j = 0;
		while (env[i][j] != '=')
		{
			key[j] = env[i][j];
			j++;
		}
		key[j] = 0;
		while (env[i][j + k])
			k++;
		value = malloc(k + 1);
		k = 0;
		while (env[i][j + k])
		{
			value[k] = env[i][j + k];
			k++;
		}
		lst_push_back(&(info->envp_list) ,lst_new((void *)key, (void *)value));
		i++;
	}
}