/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammemes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:00:57 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:37:49 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

static void	*p_malloc(t_list *head)
{
	t_list	**ret;

	ret = malloc(sizeof(t_list *));
	if (!ret)
		malloc_err();
	*ret = head;
	return ((void *)ret);
}

static void	init_arr(t_list **arr)
{
	arr[1] = NULL;
	arr[2] = NULL;
	if (ft_strcmp(arr[0]->key, "pipe"))
		arr[0] = arr[0]->next;
}

// arr[0] = curr
// arr[1] = keys
// arr[2] = values
void	create_grammemes(t_info *info)
{
	t_list	*arr[3];

	arr[0] = info->tokens;
	while (arr[0])
	{
		init_arr(arr);
		while (arr[0] && !ft_strcmp(arr[0]->key, "pipe"))
		{
			if (is_redir(arr[0]->key))
			{
				lst_pb(&arr[2], lst_new(ft_strdup(arr[0]->key),
						ft_strdup(arr[0]->next->value)));
				arr[0] = arr[0]->next->next;
			}
			else
			{
				lst_pb(&arr[1], lst_new(ft_strdup(arr[0]->key),
						ft_strdup(arr[0]->value)));
				arr[0] = arr[0]->next;
			}
		}
		lst_pb(&info->grammemes, lst_new(p_malloc(arr[1]), p_malloc(arr[2])));
	}
}
