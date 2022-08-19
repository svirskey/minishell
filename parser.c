/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:01:04 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 21:21:26 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	is_redir(const char *str)
{
	if (ft_strcmp(str, "append") || ft_strcmp(str, "write")
		|| ft_strcmp(str, "heredoc") || ft_strcmp(str, "read"))
		return (1);
	return (0);
}

static int	check_parsing(t_info *info)
{
	t_list	*curr;
	t_list	*next;

	if (!info->tokens)
		return (1);
	if (ft_strcmp(info->tokens->key, "pipe"))
	{
		print_error("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	curr = info->tokens;
	next = curr->next;
	while (curr)
	{
		if (!next)
		{
			if (!ft_strcmp(curr->key, "word"))
			{
				print_error("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			return (0);
		}
		if ((is_redir(curr->key) && !ft_strcmp(next->key, "word"))
			|| (ft_strcmp(curr->key, "pipe") && ft_strcmp(next->key, "pipe")))
		{
			print_error("minishell: syntax error near unexpected token `");
			print_error((char *)next->value);
			print_error("'\n");
			return (1);
		}
		curr = next;
		next = next->next;
	}
	return (0);
}

static void	*ptr_malloc(t_list *head)
{
	t_list	**ret;

	ret = malloc(sizeof(t_list *));
	*ret = head;
	return ((void *)ret);
}

static void	create_grammemes(t_info *info)
{
	t_list	*curr;
	t_list	*keys;
	t_list	*values;

	curr = info->tokens;
	while (curr)
	{
		keys = NULL;
		values = NULL;
		if (ft_strcmp(curr->key, "pipe"))
			curr = curr->next;
		while (curr && !ft_strcmp(curr->key, "pipe"))
		{
			if (is_redir(curr->key))
			{
				lst_push_back(&values, lst_new(ft_strdup(curr->key), ft_strdup(curr->next->value)));
				curr = curr->next->next;
			}
			else
			{
				lst_push_back(&keys, lst_new(ft_strdup(curr->key), ft_strdup(curr->value)));
				curr = curr->next;
			}
		}
		lst_push_back(&info->grammemes, lst_new(ptr_malloc(keys), ptr_malloc(values)));
	}
}

int	parser(t_info *info)
{
	opening(info);
	//lst_print(info->tokens);
	merge(info);
	//lst_print(info->tokens);
	lst_remove_node(&info->tokens, "space");
	//lst_print(info->tokens);
	if (check_parsing(info))
	{
		info->exit_status = 2;
		return (1);
	}
	create_grammemes(info);
	return (1);
}
