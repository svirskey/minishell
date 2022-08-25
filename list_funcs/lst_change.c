/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:58:13 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:38:32 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft_funcs.h"

t_list	*lst_new(void *key, void *value)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		malloc_err();
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

// changed del to pointer to el next after deleted
void	lst_remove(t_list **head, t_list **del)
{
	t_list	*prev;

	if (*head == *del)
	{
		prev = *del;
		*del = (*del)->next;
		lst_free_node(&prev);
		*head = *del;
	}
	else
	{
		prev = *head;
		while (prev->next && prev->next != *del)
			prev = prev->next;
		prev->next = (*del)->next;
		lst_free_node(del);
		*del = prev->next;
	}
}

void	lst_remove_nodes(t_list **head, char *key)
{
	t_list	*curr;

	curr = *head;
	while (curr)
	{
		if (ft_strcmp(curr->key, key))
			lst_remove(head, &curr);
		else
			curr = curr->next;
	}
}
