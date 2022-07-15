/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:58:13 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 21:02:25 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "stdlib.h"

t_list	*ft_lstnew(char *key, char *value)
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_list_clear(t_list **lst)
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
