/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:17:28 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 16:54:30 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

void	envp_init(t_info *info, char **env)
{
	int		i;
	char	*arr[3];

	i = 0;
	while (env[i])
	{
		env_parse(arr, env[i]);
		lst_pb(&(info->envp_list), lst_new(arr[0], arr[2]));
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

static char	*get_second_arg(t_list *tmp, int flag)
{
	char	*ret;
	char	*tmp_str;

	ret = NULL;
	if (flag == ENV)
		ret = ft_strjoin("=", tmp->value);
	else if (flag == EXPORT)
	{
		tmp_str = ft_strjoin("=\"", tmp->value);
		ret = ft_strjoin(tmp_str, "\"");
		free(tmp_str);
	}
	return (ret);
}

void	envp_update(t_info *info, int flag)
{
	int		i;
	t_list	*tmp;
	char	*second;

	tmp = info->envp_list;
	if (!info->envp_upd)
		return ;
	envp_clear(&info->envp_arr);
	info->envp_arr = malloc(sizeof(char *) * (lst_len(info->envp_list) + 1));
	i = 0;
	tmp = info->envp_list;
	while (i < lst_len(info->envp_list))
	{	
		second = get_second_arg(tmp, flag);
		info->envp_arr[i] = ft_strjoin(tmp->key, get_second_arg(tmp, flag));
		free(second);
		tmp = tmp->next;
		i++;
	}
	info->envp_arr[i] = NULL;
	info->envp_upd = 0;
}
