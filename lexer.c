/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:39:43 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/19 19:40:40 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

int next_char(char *str, int begin, char origin) // begin with next el
{
	int c;

	c = begin;
	if (!str)
		return -1;
	while (str[c] && str[c] != origin)
		c++;
	if (!str[c])
		return -1;
	return c - begin;
}

static int is_sep(char *str, int i)
{
	
	if (ft_isspace(str[i]))
		return 1;
	if (str[i] == '<' || str[i] == '>' || str[i] == '|' )
		return 1;
	if ((str[i] == '\'' || str[i] == '\"') && next_char(str, i + 1, str[i]) != -1)
		return 1;
	return 0;
}

static char *lst_last_key(t_list *lst)
{
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst ->next;
	return ((char *)lst->key);
}

static void lexer_space(t_info *info, char *str, int *i)
{
	if (!ft_strcmp(lst_last_key(info->tokens),"space") && ft_isspace(str[*i]))
		lst_push_back(&info->tokens, lst_new(ft_strdup("space"), ft_strdup(" ")));
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

static void lexer_spec(t_info *info, char *str, int *i)
{
	if (str[*i] == '|')
		lst_push_back(&info->tokens, lst_new(ft_strdup("pipe"), ft_strdup("|")));
	else if (str[*i] == '<')
	{
		if (str[*i + 1] && str[*i + 1] == '<')
		{
			lst_push_back(&info->tokens, lst_new(ft_strdup("heredoc"), ft_strdup("<<")));
			(*i)++;
		}
		else
			lst_push_back(&info->tokens, lst_new(ft_strdup("read"), ft_strdup("<")));
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] && str[*i + 1] == '>')
		{
			lst_push_back(&info->tokens, lst_new(ft_strdup("append"), ft_strdup(">>")));
			(*i)++;
		}
		else
			lst_push_back(&info->tokens, lst_new(ft_strdup("write"), ft_strdup(">")));
	}
	(*i)++;
}

static void lexer_quotes(t_info *info, char *str, int *i)
{
	(*i)++;
	if (str[*i] == '\'')
		lst_push_back(&info->tokens, lst_new(ft_strdup("squote"), ft_substr(str, *i, next_char(str, *i, str[*i - 1]))));
	else
		lst_push_back(&info->tokens, lst_new(ft_strdup("dquote"), ft_substr(str, *i, next_char(str, *i, str[*i - 1]))));
	*i += next_char(str, *i, str[*i - 1]) + 1;
}

static void lexer_word(t_info *info, char *str, int *i)
{
	int from = *i;
	while (str[*i] && !is_sep(str, *i))
		(*i)++;
	lst_push_back(&info->tokens, lst_new(ft_strdup("word"), ft_substr(str, from, *i - from)));
}

void lexer(t_info *info, char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		lexer_space(info, str, &i);

		if (!str[i])
			break;

		if ((str[i] == '\'' || str[i] == '\"') && next_char(str, i + 1, str[i]) != -1)
			lexer_quotes(info, str, &i);
		else if (str[i] == '<' || str[i] == '|' || str[i] == '>')
			lexer_spec(info, str, &i);
		else 
			lexer_word(info, str, &i);
	}
	// separators : \f \n \r \t \v space < > << >> | ' ""

}