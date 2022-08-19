/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:58:13 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 16:54:30 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

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

void	lst_pb(t_list **lst, t_list *node)
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

void	lst_replace(t_list *lst, char *key, char *new_value)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, key))
		{
			free(lst->value);
			lst->value = ft_strdup(new_value);
			return ;
		}
		lst = lst->next;
	}
}

static void	lst_rm(t_list **head, t_list **prev, t_list **curr)
{
	if (*prev)
	{
		(*prev)->next = (*curr)->next;
		lst_free_node(curr);
		*curr = (*prev)->next;
	}
	else
	{
		*prev = *curr;
		*curr = (*curr)->next;
		lst_free_node(prev);
		*head = *curr;
		*prev = NULL;
	}
}

void	lst_remove_node(t_list **head, char *key)
{
	t_list	*curr;
	t_list	*prev;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (ft_strcmp(curr->key, key))
			lst_rm(head, &prev, &curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
