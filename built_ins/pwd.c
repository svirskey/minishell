/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:27 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:13:55 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

int	ft_pwd(t_info *info, t_list *grammeme)
{
	char	*str;
	char	buf[1000];

	(void)info;
	(void)grammeme;
	str = getcwd(buf, 1000);
	if (!str)
	{
		printf("minishell: pwd: error with pwd path\n");
		return (1);
	}
	printf("%s\n", str);
	return (0);
}
