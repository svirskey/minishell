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

static void lexer_sep(t_info *info, char *str, int *i)
{
 //TODO parsing separators
}

static void lexer_spec(t_info *info, char *str, int *i)
{
 //TODO parsing spec symbols like redirects and pipe
}

static void lexer_quotes(t_info *info, char *str, int *i)
{
 //TODO parsing quotes with finding unclosed quotes
}

static void lexer_word(t_info *info, char *str, int *i)
{
//TODO parsing simple words maybe will be eliminated
}

void lexer(t_info *info, char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		lexer_sep(info, str, *i);
		if (str[i] == '\'' || str[i] == '\"')
			lexer_quotes(info, str, &i);
		else if (str[i] == '<' || str[i] == '|' || str[i] == '>')
			lexer_spec(info, str, &i)
		else 
			lexer_word(info, str, &i);
		i++;
	}
	// separators : \f \n \r \t \v space < > << >> | ' ""
	// add separators between words for this case : 'e''c''h''o' == echo (correct)
	// echo asd'asd  -> unclosed quotes are not interpretating
	// echo $PWD != echo $P'W'D => read till spec symbol
}