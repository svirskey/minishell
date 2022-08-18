/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:11:07 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 20:11:15 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

void	*lst_copy_value(t_list *lst, void *key)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->key, (char *)key))
			return ((void *)ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*lst_get_value(t_list *lst, void *key)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->key, (char *)key))
			return ((char *)(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	lst_len(t_list *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (len);
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
