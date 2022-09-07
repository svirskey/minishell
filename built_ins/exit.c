/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:32 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 19:11:52 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "libft_funcs.h"

static int	get_str_len(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i + len] && str[i + len] != ' ')
		len++;
	return (len);
}

static void	print_required(t_info *info, char *str)
{
	write(info->std_out, "exit\n", 5);
	p_err("minishell: exit: ");
	p_err(str);
	p_err(": numeric argument required\n");
	ft_free_info(info);
	exit (2);
}

static int	check_signs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 1 && (str[i] == '-' || str[i] == '+') && str[i - 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	check_word_in_exit(t_info *info, t_list *grammeme)
{
	int			i;
	long long	exit_status;
	char		*str;

	str = (char *)grammeme->next->value;
	i = 0;
	if (get_str_len(str) > 10 || check_signs(str))
		print_required(info, str);
	while (str[i])
	{
		if ((str[i] < 48 || str[i] > 57) && str[i]
			!= '-' && str[i] != '+' && str[i] != ' ')
			print_required(info, str);
		i++;
	}
	exit_status = ft_atol(grammeme->next->value);
	if (exit_status > INT32_MAX || exit_status < INT32_MIN)
		print_required(info, str);
	write(info->std_out, "exit\n", 5);
	ft_free_info(info);
	return (exit_status);
}

int	ft_exit(t_info *info, t_list *grammeme)
{
	int			word_count;
	long long	exit_status;

	word_count = lst_len(grammeme);
	if (word_count > 2)
	{
		write(info->std_out, "exit\n", 5);
		p_err("minishell: exit: too many arguments\n");
		ft_free_info(info);
		exit (1);
	}
	else if (word_count == 1)
	{
		write(info->std_out, "exit\n", 5);
		ft_free_info(info);
		exit (0);
	}
	exit_status = check_word_in_exit(info, grammeme);
	exit (exit_status % 256);
	return (0);
}
