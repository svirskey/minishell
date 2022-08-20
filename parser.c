/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:01:04 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 19:51:22 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

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

int	is_redir(const char *str)
{
	if (ft_strcmp(str, "append") || ft_strcmp(str, "write")
		|| ft_strcmp(str, "heredoc") || ft_strcmp(str, "read"))
		return (1);
	return (0);
}

static int	check_error(t_list **curr, t_list **next)
{
	while (*curr)
	{
		if (!(*next))
		{
			if (!ft_strcmp((*curr)->key, "word"))
			{
				p_error("minishell: syntax error near ");
				p_error("unexpected token `newline'\n");
				return (1);
			}
			return (0);
		}
		if ((is_redir((*curr)->key) && !ft_strcmp((*next)->key, "word"))
			|| (ft_strcmp((*curr)->key, "pipe")
				&& ft_strcmp((*next)->key, "pipe")))
		{
			p_error("minishell: syntax error near unexpected token `");
			p_error((char *)(*next)->value);
			p_error("'\n");
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
		return (1);
	if (ft_strcmp(info->tokens->key, "pipe"))
	{
		p_error("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	curr = info->tokens;
	next = curr->next;
	if (check_error(&curr, &next))
		return (1);
	return (0);
}

int	parser(t_info *info)
{
	opening(info);
	merge(info);
	lst_remove_node(&info->tokens, "space");
	if (check_parsing(info))
	{
		info->exit_status = 2;
		return (1);
	}
	create_grammemes(info);
	return (0);
}
