/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 19:41:28 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

static int	check_len(t_list *grammeme)
{
	int	len;

	len = lst_len(grammeme);
	if (len != 2)
	{
		if (len > 2)
			print_error("minishell: cd: too many arguments\n");
		else
			print_error("minishell: cd: too few arguments\n");
		return (1);
	}
	return (0);
}

int	ft_cd(t_info *info, t_list *grammeme)
{
	if (check_len(grammeme))
		return (1);
	if (chdir(grammeme->next->value) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	else
	{
		if (!lst_get_value(info->envp_list, "OLDPWD"))
			lst_push_back(&(info->envp_list),
				lst_new(ft_strdup("OLDPWD"), ft_strdup("")));
		lst_replace(info->envp_list, "OLDPWD",
			lst_get_value(info->envp_list, "OLDPWD"));
		lst_replace(info->envp_list, "PWD", grammeme->next->value);
	}
	return (0);
}
