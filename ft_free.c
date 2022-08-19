/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:55:54 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 16:56:09 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

void	ft_free_grammemes(t_info *info)
{
	t_list	*tmp;

	tmp = info->grammemes;
	while (tmp)
	{
		lst_clear((t_list **)tmp->key);
		lst_clear((t_list **)tmp->value);
		tmp = tmp->next;
	}
	lst_clear(&info->grammemes);
}

void	ft_free_info(t_info *info)
{
	lst_clear(&info->builtins);
	lst_clear(&info->envp_list);
	lst_clear(&info->tokens);
	close(info->std_in);
	close(info->std_out);
	ft_free_grammemes(info);
	envp_clear(&info->envp_arr);
}
