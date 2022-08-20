/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 18:22:03 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

char	*get_path(t_info *info, t_list *grammeme)
{
	if (!grammeme->next)
		return (lst_get_value(info->envp_list, "HOME"));
	else
		return (grammeme->next->value);
}

int	ft_cd(t_info *info, t_list *grammeme)
{
	char	*path;

	path = get_path(info, grammeme);
	if (!path || path[0] == 0)
	{
		p_error("minishell: cd: HOME not set\n");
		return (1);
	}
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
