/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:39:43 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/19 17:10:45 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "libft_funcs.h"

// begin with next el
int	next_char(char *str, int begin, char origin)
{
	int	c;

	c = begin;
	if (!str)
		return (-1);
	while (str[c] && str[c] != origin)
		c++;
	if (!str[c])
		return (-1);
	return (c - begin);
}

static void	spec_push(t_info *info, int type)
{
	if (type == PIPE)
		lst_pb(&info->tokens,
			lst_new(ft_strdup("pipe"), ft_strdup("|")));
	else if (type == HEREDOC)
		lst_pb(&info->tokens,
			lst_new(ft_strdup("heredoc"), ft_strdup("<<")));
	else if (type == READ)
		lst_pb(&info->tokens,
			lst_new(ft_strdup("read"), ft_strdup("<")));
	else if (type == APPEND)
		lst_pb(&info->tokens,
			lst_new(ft_strdup("append"), ft_strdup(">>")));
	else if (type == WRITE)
		lst_pb(&info->tokens,
			lst_new(ft_strdup("write"), ft_strdup(">")));
}

void	lexer_spec(t_info *info, char *str, int *i)
{
	if (str[*i] == '|')
		spec_push(info, PIPE);
	else if (str[*i] == '<')
	{
		if (str[*i + 1] && str[*i + 1] == '<')
		{
			spec_push(info, HEREDOC);
			(*i)++;
		}
		else
			spec_push(info, READ);
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] && str[*i + 1] == '>')
		{
			spec_push(info, APPEND);
			(*i)++;
		}
		else
			spec_push(info, WRITE);
	}
	(*i)++;
}

void	lexer(t_info *info, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		lexer_space(info, str, &i);
		if (!str[i])
			break ;
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (next_char(str, i + 1, str[i]) == -1)
			{
				p_err("minishell: Error! Unclosed brackets!\n");
				info->exit_status = 2;
				lst_clear(&info->tokens);
				return ;
			}
			else
				lexer_quotes(info, str, &i);
		}
		else if (str[i] == '<' || str[i] == '|' || str[i] == '>')
			lexer_spec(info, str, &i);
		else
			lexer_word(info, str, &i);
	}
}
