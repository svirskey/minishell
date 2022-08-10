/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:36 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 19:39:54 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int	ft_echo(t_info *info, t_list *grammeme)
{
	(void)info;

	grammeme = grammeme->next;
	while (grammeme)
	{
		printf("%s", grammeme->value);
		if (grammeme->next)
			printf(" ");
		grammeme = grammeme->next;
	}
	printf("\n");
	return 0;
}
