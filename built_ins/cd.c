/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 13:49:17 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

int	ft_cd(t_info *info, t_list *grammeme)
{
	char	*path;

	if (!grammeme->next)
		path = "/";
	else
		path = grammeme->next->value;
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	else
	{
		if (!lst_get_value(info->envp_list, "OLDPWD"))
			lst_pb(&(info->envp_list),
				lst_new(ft_strdup("OLDPWD"), ft_strdup("")));
		lst_replace(info->envp_list, "OLDPWD",
			lst_get_value(info->envp_list, "OLDPWD"));
		lst_replace(info->envp_list, "PWD", path);
	}
	return (0);
}
