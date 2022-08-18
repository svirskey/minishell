/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:10:08 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 20:10:22 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

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
