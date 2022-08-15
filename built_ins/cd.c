/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:16:58 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

int	ft_cd(t_info *info, t_list *grammeme)
{
	int		len;
	char	*dir;

	len = lst_len(grammeme);
	if (len == 2)
		dir = grammeme->next->value;
	else
	{
		if (len > 2)
			write(STDERR_FILENO, "minishell: cd: too many arguments\n", 35);
		else
			write(STDERR_FILENO, "minishell: cd: too few arguments\n", 34);
		return (1);
	}
	if (chdir(dir) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	else
	{
		if (!lst_get_value(info->envp_list, "OLDPWD"))
			lst_push_back(&(info->envp_list), lst_new(ft_strdup("OLDPWD"), ft_strdup("")));
		lst_replace(info->envp_list, "OLDPWD", lst_get_value(info->envp_list, "OLDPWD"));
		lst_replace(info->envp_list, "PWD", dir);
	}
	return (0);
}
