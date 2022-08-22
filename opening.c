/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:17:15 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 18:38:30 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	c_to_sep(char *str, int begin, int type)
{
	int	c;

	c = begin;
	if (!str)
		return (0);
	if (type == DOLLAR)
	{
		while (str[c] && str[c] != '$')
			c++;
	}
	else if (type == BOTH)
	{
		while (str[c] && str[c] != '$' && str[c] != ' ')
			c++;
	}
	return (c - begin);
}

static void	expanding(t_info *info, t_list *tmp, t_list **opn, int *i)
{
	char	*ret;

	ret = ft_substr(tmp->value, *i, c_to_sep(tmp->value, *i, BOTH));
	if (ret)
	{
		if (lst_get_value(info->envp_list, ret))
			lst_pb(opn, lst_new(ft_strdup("word"),
					ft_strdup(lst_get_value(info->envp_list, ret))));
		else
			lst_pb(opn, lst_new(ft_strdup("word"), ft_strdup("")));
		free(ret);
	}
	*i += c_to_sep(tmp->value, *i, BOTH);
}

static void	exp_other(t_info *info, t_list *tmp, t_list **opn, int *i)
{
	if (!((char *)tmp->value)[*i])
		lst_pb(opn, lst_new(ft_strdup("word"), ft_strdup("$")));
	else if (((char *)tmp->value)[*i] == ' ')
	{
		lst_pb(opn, lst_new(ft_strdup("word"), ft_strdup("$ ")));
		(*i)++;
	}
	else if (((char *)tmp->value)[*i] == '$')
	{
		lst_pb(opn, lst_new(ft_strdup("word"), ft_itoa((int)getpid())));
		(*i)++;
	}
	else if (((char *)tmp->value)[*i] == '?')
	{
		lst_pb(opn, lst_new(ft_strdup("word"), ft_itoa(info->exit_status)));
		(*i)++;
	}
	else
		expanding(info, tmp, opn, i);
}

static void	find_type(t_info *info, t_list *tmp, t_list **opn, int *i)
{
	if (((char *)tmp->value)[*i] == '$')
	{
		(*i)++;
		exp_other(info, tmp, opn, i);
	}
	else
	{
		lst_pb(opn, lst_new(ft_strdup("word"), ft_substr(tmp->value,
					*i, c_to_sep(tmp->value, *i, DOLLAR))));
		*i += c_to_sep(tmp->value, *i, DOLLAR);
	}
}

void	inner_open(t_info *info, t_list **prev, t_list **tmp)
{
	t_list	*opn;
	t_list	*cur;
	int		i;

	i = 0;
	opn = NULL;
	while (((char *)(*tmp)->value)[i])
		find_type(info, *tmp, &opn, &i);
	if (*prev)
		(*prev)->next = opn;
	cur = opn;
	while (cur->next)
		cur = cur->next;
	cur->next = (*tmp)->next;
	if (*tmp == info->tokens)
		info->tokens = opn;
	lst_free_node(tmp);
	*tmp = cur;	
}
