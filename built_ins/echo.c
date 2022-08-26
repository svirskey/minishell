/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:36 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:12:15 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_funcs.h"
#include "minishell.h"
#include "libft_funcs.h"
#include <stdio.h>

int	ft_echo(t_info *info, t_list *grammeme)
{
	(void)info;
	int is_param;

	is_param = 0;
	grammeme = grammeme->next;
	if (grammeme)
	{
		if (ft_strncmp(grammeme->value, "-n", 2) == 0)
		{
			is_param = 1;
			grammeme = grammeme->next;
		}
		else
			is_param = 0;
	}
	while (grammeme)
	{
		printf("%s", (char *)grammeme->value);
		if (grammeme->next)
			printf(" ");
		grammeme = grammeme->next;
	}
	if (!is_param)
		printf("\n");
	return (0);
}
