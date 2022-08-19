/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:27:32 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 01:36:05 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../minishell.h"

static int get_str_len(char *str)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i + len] && str[i + len] != ' ')
		len++;
	return (len);
}

static int	check_word_in_exit(t_info *info, t_list *grammeme)
{
	int			i;
	long long	exit_status;
	char		*str;

	str = (char *)grammeme->next->value;
	i = 0;
	if (get_str_len(str) > 10)
	{
		print_error("exit\nminishel: exit: ");
		print_error(str);
		print_error(" int argument required");
		ft_free_info(info);
		exit (2);
	}
	while (str[i])
	{
		if ((str[i] < 48 || str[i] > 57) && str[i] != '-' && str[i] != '+')
		{
			print_error("exit\nminishel: exit: ");
			print_error(str);
			print_error(" int argument required");
			ft_free_info(info);
			exit (2);
		}
		i++;
	}
	exit_status = ft_atol(grammeme->next->value);
	if (exit_status > INT32_MAX || exit_status < INT32_MIN)
	{
		print_error("exit\nminishel: exit: ");
		print_error(str);
		print_error(" int argument required");
		ft_free_info(info);
		exit(2);
	}
	print_error("exit\n");
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
		print_error("exit\nminishell: exit: too many arguments\n");
		ft_free_info(info);
		exit (1);
	}
	else if (word_count == 1)
	{
		print_error("exit\n");
		ft_free_info(info);
		exit (0);
	}
	exit_status = check_word_in_exit(info, grammeme);
	exit (exit_status % 256);
	return (0);
}
