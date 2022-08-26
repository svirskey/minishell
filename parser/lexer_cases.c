/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:16:27 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 16:54:30 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

static char	*lst_last_key(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst ->next;
	return ((char *)lst->key);
}

static int	is_sep(char *str, int i)
{
	if (ft_isspace(str[i]))
		return (1);
	if (str[i] == '<' || str[i] == '>' || str[i] == '|'
		|| (str[i] == '\'' || str[i] == '\"'))
		return (1);
	return (0);
}

void	lexer_word(t_info *info, char *str, int *i)
{
	int	from;

	from = *i;
	while (str[*i] && !is_sep(str, *i))
		(*i)++;
	lst_pb(&info->tokens,
		lst_new(ft_strdup("word"), ft_substr(str, from, *i - from)));
}

void	lexer_space(t_info *info, char *str, int *i)
{
	if (!ft_strcmp(lst_last_key(info->tokens), "space") && ft_isspace(str[*i]))
		lst_pb(&info->tokens,
			lst_new(ft_strdup("space"), ft_strdup(" ")));
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

void	lexer_quotes(t_info *info, char *str, int *i)
{
	(*i)++;
	if (str[*i - 1] == '\'')
		lst_pb(&info->tokens,
			lst_new(ft_strdup("squote"),
				ft_substr(str, *i, next_char(str, *i, str[*i - 1]))));
	else
		lst_pb(&info->tokens,
			lst_new(ft_strdup("dquote"),
				ft_substr(str, *i, next_char(str, *i, str[*i - 1]))));
	*i += next_char(str, *i, str[*i - 1]) + 1;
}
