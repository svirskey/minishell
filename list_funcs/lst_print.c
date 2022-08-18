/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:09:00 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 20:12:19 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

void	lst_print(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("[%s]  \t-> [%s]\n", (char *)tmp->key, (char *)tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

void	lst_print_grammemes(t_list *grammemes)
{
	t_list	*tmp;

	tmp = grammemes;
	printf("Printing grammemes:\n");
	while (tmp)
	{
		printf("\nNext Pipe Part:\n");
		lst_print(*(t_list **)tmp->key);
		printf("\n");
		lst_print(*(t_list **)tmp->value);
		tmp = tmp->next;
	}
}
