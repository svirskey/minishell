/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:30 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 19:51:47 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

static int	check_single(t_info *info, t_list *grammeme)
{
	int	i;

	if (lst_len(grammeme) == 1)
	{
		envp_update(info, EXPORT);
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

static int	check_minus(char *ref)
{
	int	i;

	i = 0;
	while (ref[i])
	{
		if (ref[i] == '-')
		{
			if (!ref[i + 1] || ref[i + 1] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_grammeme(t_info *info, t_list *grammeme, char **arr)
{
	char	c;

	c = ((char *)grammeme->value)[0];
	if ((c < 'a' || c > 'z') && c != '_' && (c < 'A' || c > 'Z'))
	{
		p_error("minishell: export: `");
		p_error((char *)grammeme->value);
		p_error("': not a valid identifier\n");
		return (1);
	}
	else
	{
		env_parse(arr, grammeme->value);
		if (check_minus(arr[0]))
		{
			free(arr[0]);
			free(arr[1]);
			free(arr[2]);
			p_error("minishell: export: `");
			p_error((char *)grammeme->value);
			p_error("': not a valid identifier\n");
			return (1);
		}
		if (ft_strcmp(arr[1], "="))
		{
			lst_remove_nodes(&info->envp_list, arr[1]);
			lst_pb(&info->envp_list, lst_new(arr[0], arr[2]));
		}
		else
		{
			free(arr[0]);
			free(arr[2]);
		}
		free(arr[1]);
		return (0);
	}
}

int	ft_export(t_info *info, t_list *grammeme)
{
	char	*arr[3];
	int		exit_code;

	if (check_single(info, grammeme))
		return (0);
	exit_code = 0;
	grammeme = grammeme->next;
	while (grammeme)
	{
		if (check_grammeme(info, grammeme, arr))
			exit_code = 1;
		grammeme = grammeme->next;
	}
	info->envp_status = KO;
	return (exit_code);
}
