/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:17:28 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 23:03:10 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

void	envp_init(t_info *info, char **env)
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
		j++;
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

void envp_clear(char ***arr)
{
	int len;
	char **tmp;

	tmp = *arr;
	len = 0;
	if (!(*arr))
		return ;
	while (tmp[len])
	{
		free(tmp[len]);
		len++;
	}
	free(*arr);
	*arr = NULL;
}

void envp_update(t_info *info)
{
	int len;
	int i;
	t_list *tmp;

	tmp = info->envp_list;
	len = 0;
	if (!info->envp_upd)
		return ;
	envp_clear(&info->envp_arr);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	info->envp_arr = malloc(sizeof(char *) * (len + 1));
	i = 0;
	tmp = info->envp_list;
	while (i < len)
	{
		info->envp_arr[i] = ft_strjoin(tmp->key, ft_strjoin("=",tmp->value));
		tmp = tmp->next;
		i++;
	}
	info->envp_arr[i] = NULL;
	info->envp_upd = 0;
}
