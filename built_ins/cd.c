/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 09:53:27 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "libft_funcs.h"

char	*get_path(t_info *info, t_list *grammeme)
{
	if (!grammeme->next)
		return (lst_get_value(info->envp_list, "HOME"));
	else
		return (grammeme->next->value);
}

static char	*get_pwd(void)
{
	char	buf[1000];
	char	*pwd;

	pwd = getcwd(buf, 1000);
	return (pwd);
}

int	ft_cd(t_info *info, t_list *grammeme)
{
	char	*path;

	path = get_path(info, grammeme);
	if (!path || path[0] == 0)
	{
		p_err("minishell: cd: HOME not set\n");
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
			lst_get_value(info->envp_list, "PWD"));
		lst_replace(info->envp_list, "PWD", get_pwd());
	}
	return (0);
}
