/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 19:39:25 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int	ft_cd(t_info *info, t_list *grammeme)
{
	int		status;
	int		len;
	char	*dir;

	len = lst_len(grammeme);
	if (len > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (len == 2)
		dir = grammeme->next->value;
	else
	{
		dir = lst_get_value(info->envp_list, "HOME");
		if (!dir)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		if (ft_strcmp(dir, ""))
			return 0;
	}
	status = chdir(dir);
	if (status == -1)
	{
		printf("minishell: cd: %s No such file or directory\n", dir);
		return (1);
	}
	else
	{
		if (!lst_get_value(info->envp_list, "OLDPWD"))
			lst_push_back(&(info->envp_list) ,lst_new(ft_strdup("OLDPWD"), ft_strdup("")));
		lst_replace(info->envp_list, "OLDPWD", lst_get_value(info->envp_list, "OLDPWD"));
		lst_replace(info->envp_list, "PWD", dir);
	}
	return (0);
}
