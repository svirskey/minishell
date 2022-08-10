/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:58:13 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 18:48:56 by bfarm            ###   ########.fr       */
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

void	lst_free_node(t_list **node)
{
	free((*node)->key);
	free((*node)->value);
	free(*node);
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
		lst_free_node(&tmp);
	}
	*lst = NULL;
}

void	lst_print(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("[%s]  \t-> [%s]\n",(char *)tmp->key, (char *)tmp->value);
		tmp = tmp->next;
	}
}

void	lst_print_grammemes(t_list *grammemes)
{
	t_list *tmp;

	tmp = grammemes;
	printf("Printing grammemes:\n");
	while (tmp)
	{
		printf("\nNext Pipe Part:\n");
		lst_print(*(t_list **)tmp->key);
		printf("\n");
		lst_print(*(t_list **)tmp->value);
		tmp = tmp->next;
	}
}

void	*lst_copy_value(t_list *lst, void *key)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->key, (char *)key))
			return (void *)ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return ft_strdup("");
}

char	*lst_get_value(t_list *lst, void *key)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->key, (char *)key))
			return (char *)(tmp->value);
		tmp = tmp->next;
	}
	return NULL;
}

int	lst_len(t_list *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return len;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return len;
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

void	lst_remove_node(t_list **head, char *key)
{
	t_list	*curr;
	t_list	*prev;

	if (!(*head))
		return ;
	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (ft_strcmp(curr->key, key))
		{
			if (prev)
			{
				prev->next = curr->next;
				lst_free_node(&curr);
				curr = prev->next;
			}
			else
			{
				prev = curr;
				curr = curr->next;
				lst_free_node(&prev);
				*head = curr;
				prev = NULL;
			}
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
