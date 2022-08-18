/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:17:15 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 21:17:53 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	chars_to_separ(char *str, int begin, int type)
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

void	opening(t_info *info)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*opn;
	int		i;

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
			{
				opn = NULL;
				i = 0;
				while (((char *)tmp->value)[i])
				{
					if (((char *)tmp->value)[i] == '$')
					{
						i++;
						if (!((char *)tmp->value)[i])
						{
							lst_push_back(&opn, lst_new(ft_strdup("word"), ft_strdup("$")));
							break ;
						}
						else if (((char *)tmp->value)[i] == ' ')
						{
							lst_push_back(&opn, lst_new(ft_strdup("word"), ft_strdup("$ ")));
							i++;
						}
						else if (((char *)tmp->value)[i] == '$')
						{
							lst_push_back(&opn, lst_new(ft_strdup("word"), ft_itoa((int)getpid())));
							i++;
						}
						else if (((char *)tmp->value)[i] == '?')
						{
							lst_push_back(&opn, lst_new(ft_strdup("word"), ft_itoa(info->exit_status)));
							i++;
						}
						else
						{
							char * ret = ft_substr(tmp->value, i, chars_to_separ(tmp->value, i, BOTH));
							if (ret)
							{
								if (lst_get_value(info->envp_list, ret))
									lst_push_back(&opn, lst_new(ft_strdup("word"), ft_strdup(lst_get_value(info->envp_list, ret))));
								else
									lst_push_back(&opn, lst_new(ft_strdup("word"), ft_strdup("")));
								free(ret);
							}
							i += chars_to_separ(tmp->value, i, BOTH);
						}
					}
					else
					{
						lst_push_back(&opn, lst_new(ft_strdup("word"), ft_substr(tmp->value, i, chars_to_separ(tmp->value, i, DOLLAR))));
						i += chars_to_separ(tmp->value, i, DOLLAR);
					}
				}
				if (prev)
					prev->next = opn;
				while (opn->next)
					opn = opn->next;
				opn->next = tmp->next;
				lst_free_node(&tmp);
				if (tmp == info->tokens)
					info->tokens = opn;
				else
					tmp = opn;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
