/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:17:28 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:24:38 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

void	env_parse(char **arr, char *str)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (str[j] && str[j] != '=')
		j++;
	arr[0] = malloc(j + 1);
	j = 0;
	while (str[j] && str[j] != '=')
	{
		arr[0][j] = str[j];
		j++;
	}
	arr[0][j] = 0;
	if (str[j] == '=')
		arr[1] = ft_strdup("=");
	else
		arr[1] = ft_strdup("");
	j++;
	while (str[j + k])
		k++;
	arr[2] = malloc(k + 1);
	k = 0;
	while (str[j + k])
	{
		arr[2][k] = str[j + k];
		k++;
	}
}

void	envp_init(t_info *info, char **env)
{
	int		i;
	char	*arr[3];

	i = 0;
	while (env[i])
	{
		env_parse(arr, env[i]);
		lst_push_back(&(info->envp_list), lst_new(arr[0], arr[2]));
		free(arr[1]);
		i++;
	}
}

void	envp_clear(char ***arr)
{
	int		len;
	char	**tmp;

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

void	envp_update(t_info *info)
{
	int		len;
	int		i;
	t_list	*tmp;

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
		info->envp_arr[i] = ft_strjoin(tmp->key, ft_strjoin("=", tmp->value));
		tmp = tmp->next;
		i++;
	}
	info->envp_arr[i] = NULL;
	info->envp_upd = 0;
}
