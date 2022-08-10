/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:23 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 18:37:26 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int	ft_unset(t_info *info, t_list *grammeme)
{
	t_list	*lst;

	if (lst_len(grammeme) == 1)
		return 0;
	lst = grammeme->next;
	while (lst)
	{
		lst_remove_node(&info->envp_list, lst->value);
		lst = lst->next;
	}
	info->envp_upd = 1;
	return 0;
}
