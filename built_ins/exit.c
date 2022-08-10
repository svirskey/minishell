/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:32 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:13:08 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

int	ft_exit(t_info *info, t_list *grammeme)
{
	int			word_count;
	long long	exit_status;

	word_count = lst_len(grammeme);
	if (word_count > 2)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		ft_free_info(info);
		exit (1);
	}
	else if (word_count == 1)
	{
		printf("exit\n");
		ft_free_info(info);
		exit (0);
	}
	exit_status = ft_atol(grammeme->next->value);
	printf("exit\n");
	ft_free_info(info);
	if (exit_status > INT32_MAX || exit_status < INT32_MIN)
		exit(2);
	else
		exit (exit_status % 256);
	return (0);
}
