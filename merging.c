/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:21:08 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 21:42:22 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

static void	find_len(t_list **arr, char **new_str)
{
	int	len;

	len = 0;
	arr[0] = arr[2];
	while (arr[2] && ft_strcmp(arr[2]->key, "word"))
	{
		len += ft_strlen(arr[2]->value);
		arr[2] = arr[2]->next;
	}
	arr[2] = arr[0];
	*new_str = malloc(sizeof(char) * (len + 1));
	ft_bzero(*new_str, len + 1);
	while (arr[2] && ft_strcmp(arr[2]->key, "word"))
	{
		ft_strlcat(*new_str, arr[2]->value, len + 1);
		arr[2] = arr[2]->next;
	}
}

static void	add_nodes(t_info *info, t_list **arr, char *new_str)
{
	if (arr[0] == info->tokens)
	{
		info->tokens = lst_new(ft_strdup("word"), new_str);
		info->tokens->next = arr[2];
	}
	else
	{
		arr[1]->next = lst_new(ft_strdup("word"), new_str);
		arr[1]->next->next = arr[2];
	}
	while (arr[0] && ft_strcmp(arr[0]->key, "word"))
	{
		arr[2] = arr[0];
		arr[0] = arr[0]->next;
		lst_free_node(&arr[2]);
	}
}

//arr[0] = begin
//arr[1] = prev
//arr[2] = tmp

void	merge(t_info *info)
{
	t_list	*arr[3];
	char	*new_str;

	new_str = NULL;
	arr[2] = info->tokens;
	arr[1] = NULL;
	while (arr[2])
	{
		if (ft_strcmp(arr[2]->key, "word") && arr[2]->next
			&& ft_strcmp(arr[2]->next->key, "word"))
		{
			find_len(arr, &new_str);
			add_nodes(info, arr, new_str);
			if (!arr[0])
				break ;
			arr[2] = arr[0];
		}
		arr[1] = arr[2];
		arr[2] = arr[2]->next;
	}
}
