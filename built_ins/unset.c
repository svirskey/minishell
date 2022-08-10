/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:23 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 19:40:27 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int	ft_unset(t_info *info, t_list *grammeme)
{
	(void)info;
	t_list *lst;

	lst = grammeme->next;
	while (lst)
	{
		//TODO lst_remove(t_list **lst, void *key); => remove node with key
	}
	return 0;
}
