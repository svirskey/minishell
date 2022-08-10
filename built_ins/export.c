/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:30 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:14:15 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int	ft_export(t_info *info, t_list *grammeme)
{
	char	*arr[3];
	int		exit_code;

	exit_code = 0;
	grammeme = grammeme->next;
	while (grammeme)
	{
		if (((char *)grammeme->value)[0] == '=')
		{
			printf("minishell: export: `%s': not a valid indentifier\n", (char *)grammeme->value);
			exit_code = 1;
		}
		else
		{
			parse_env(arr, grammeme->value);
			if (ft_strcmp(arr[1], "="))
			{
				lst_remove_node(&info->envp_list, arr[1]);
				lst_push_back(&info->envp_list, lst_new(arr[0], arr[2]));
				free(arr[1]);
			}
			else
			{
				free(arr[0]);
				free(arr[1]);
				free(arr[2]);
			}	
		}
		grammeme = grammeme->next;
	}

	return (exit_code);
}
