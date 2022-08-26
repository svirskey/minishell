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

#include "../structs.h"
#include "../minishell.h"

int	ft_echo(t_info *info, t_list *grammeme)
{
	(void)info;
	int is_param;

	is_param = 0;
	grammeme = grammeme->next;
	if (grammeme)
	{
		if (ft_strncmp(grammeme->value, "-n") == 1)
			is_param = 1;
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
