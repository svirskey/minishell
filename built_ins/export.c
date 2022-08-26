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
#include "../minishell.h"

static int check_single(t_info *info, t_list *grammeme)
{
	int	i;

	if (lst_len(grammeme) == 1)
	{
		envp_update(info);
		i = 0;
		while (info->envp_arr[i])
		{
			printf("declare -x %s\n", info->envp_arr[i]);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

int	ft_export(t_info *info, t_list *grammeme)
{
	char	*arr[3];
	int		exit_code;

	if (check_single(info, grammeme))
		return 0;
	exit_code = 0;
	grammeme = grammeme->next;
	while (grammeme)
	{
		if (((char *)grammeme->value)[0] == '=')
		{
			write(STDERR_FILENO, "minishell: export: `" , 21);
			write(STDERR_FILENO, (char *)grammeme->value, ft_strlen((char *)grammeme->value));
			write(STDERR_FILENO, "': not a valid indentifier\n",28);
			exit_code = 1;
		}
		else
		{
			env_parse(arr, grammeme->value);
			if (ft_strcmp(arr[1], "="))
			{
				lst_remove_node(&info->envp_list, arr[0]);
				lst_push_back(&info->envp_list, lst_new(arr[0], arr[2]));
			}
			else
			{
				free(arr[0]);
				free(arr[2]);
			}
			free(arr[1]);
		}
		grammeme = grammeme->next;
	}
	info->envp_upd = 1;
	return (exit_code);
}
