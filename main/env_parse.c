/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:13:14 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 16:52:18 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft_funcs.h"

static void	env_strdup(char **arr, char *str, int *j)
{
	arr[0][*j] = 0;
	if (str[*j] == '=')
		arr[1] = ft_strdup("=");
	else
		arr[1] = ft_strdup("");
	(*j)++;
}

void	cpy_first(char **arr, char **str, int *j)
{
	*j = 0;
	while ((*str)[*j] && (*str)[*j] != '=')
		(*j)++;
	arr[0] = malloc(*j + 1);
	if (!arr[0])
		malloc_err();
	*j = 0;
	while ((*str)[*j] && (*str)[*j] != '=')
	{
		arr[0][*j] = (*str)[*j];
		(*j)++;
	}
}

void	env_parse(char **arr, char *str)
{
	int		j;
	int		k;

	k = 0;
	cpy_first(arr, &str, &j);
	env_strdup(arr, str, &j);
	while (str[j + k])
		k++;
	arr[2] = malloc(k + 1);
	if (!arr[2])
		malloc_err();
	k = 0;
	while (str[j + k])
	{
		arr[2][k] = str[j + k];
		k++;
	}
	arr[2][k] = 0;
}
