/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:58:13 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/19 18:54:40 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "stdio.h"
#include "stdlib.h"

t_list	*lst_new(void *key, void *value)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	lst_push_back(t_list **lst, t_list *node)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	lst_clear(t_list **lst)
{
	t_list	*curr;
	t_list	*tmp;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}

void	lst_print(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("[%s]  \t-> [%s]\n",(char *)tmp->key, (char *)tmp->value);
		tmp = tmp->next;
	}
}

void *lst_get_value(t_list *lst, void *key)
{
	t_list *tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->key, (char *)key))
			return (void *)ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return ft_strdup("");
}