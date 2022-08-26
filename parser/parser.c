/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:01:04 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:42:22 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

static void	opening(t_info *info)
{
	t_list	*tmp;
	t_list	*prev;

	prev = NULL;
	tmp = info->tokens;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "squote"))
		{
			free(tmp->key);
			tmp->key = ft_strdup("word");
		}
		else if ((ft_strcmp(tmp->key, "dquote") || ft_strcmp(tmp->key, "word")))
		{
			if (next_char(tmp->value, 0, '$') == -1)
			{
				free(tmp->key);
				tmp->key = ft_strdup("word");
			}
			else
				inner_open(info, &prev, &tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static int	check_error(t_list **curr, t_list **next)
{
	while (*curr)
	{
		if (!(*next))
		{
			if (!ft_strcmp((*curr)->key, "word"))
			{
				p_err("minishell: syntax error near ");
				p_err("unexpected token `newline'\n");
				return (1);
			}
			return (0);
		}
		if ((is_redir((*curr)->key) && !ft_strcmp((*next)->key, "word"))
			|| (ft_strcmp((*curr)->key, "pipe")
				&& ft_strcmp((*next)->key, "pipe")))
		{
			p_err("minishell: syntax error near unexpected token `");
			p_err((char *)(*next)->value);
			p_err("'\n");
			return (1);
		}
		*curr = *next;
		*next = (*next)->next;
	}
	return (0);
}

static int	check_parsing(t_info *info)
{
	t_list	*curr;
	t_list	*next;

	if (!info->tokens)
		return (0);
	if (ft_strcmp(info->tokens->key, "pipe"))
	{
		p_err("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	curr = info->tokens;
	next = curr->next;
	if (check_error(&curr, &next))
		return (1);
	return (0);
}

static void	remove_empties(t_list **tokens)
{
	t_list	*tmp;

	tmp = *tokens;
	while (tmp && ft_strcmp(tmp->key, "word") && ((char *)tmp->value)[0] == 0)
		lst_remove(tokens, &tmp);
}

int	parser(t_info *info)
{
	opening(info);
	merge(info);
	lst_remove_nodes(&info->tokens, "space");
	remove_empties(&info->tokens);
	if (check_parsing(info))
	{
		info->exit_status = 2;
		return (1);
	}
	create_grammemes(info);
	return (0);
}
