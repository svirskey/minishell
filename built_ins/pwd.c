/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:27 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/08 22:23:10 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

int	ft_pwd(t_info *info, t_list *grammeme)
{
	char	*str;
	char	buf[1000];

	(void)grammeme;
	str = getcwd(buf, 1000);
	if (!str)
	{
		printf("Error with pwd path\n");
		info->exit_status = 1;
		return 1;
	}
	printf("PWD : %s\n", str);
	info->exit_status = 0;
	return 0;
}
