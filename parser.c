/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:01:04 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/06 19:06:19 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int till_sep(char *str, int begin)
{
    int c;

	c = begin;
	if (!str)
		return 0;
	while (str[c] && str[c] != '$')
		c++;
	return c - begin;
}

static void opening(t_info *info)
{
    t_list *tmp;
    t_list *prev;
    t_list *opn;
    int i;

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
                            lst_push_back(&opn, lst_new(ft_strdup("word"),ft_strdup("$")));
                            break;
                        }
                        else if (((char *)tmp->value)[i] == '$')
                        {
                             lst_push_back(&opn, lst_new(ft_strdup("word"), ft_strdup("[TODOPID]"))); // todo itoa
                             i++;
                        }
                        else if (((char *)tmp->value)[i] == '?')
                        {
                            lst_push_back(&opn, lst_new(ft_strdup("word"), ft_strdup("[TODOEXIT]"))); // todo itoa 
                            i++;
                        }
                        else
                        {
                            lst_push_back(&opn, lst_new(ft_strdup("word"), lst_get_value(info->envp_list, ft_substr(tmp->value, i, till_sep(tmp->value, i)))));
                            i += till_sep(tmp->value, i);
                        }
                    }
                    else
                    {
                        lst_push_back(&opn, lst_new(ft_strdup("word"), ft_substr(tmp->value, i, till_sep(tmp->value, i)))); 
                        i += till_sep(tmp->value, i);
                    }
                }
                prev->next = opn;
                while (opn->next)
                    opn = opn->next;
                opn->next = tmp->next;
                lst_free_node(&tmp);
                tmp = opn;
            }
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

static void merge(t_info *info)
{
    t_list *tmp;
    t_list *begin;
    t_list *prev;
    int len;
    char *new_str;

    tmp = info->tokens;
    prev = NULL;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "word") && tmp->next && ft_strcmp(tmp->next->key, "word"))
        {
            len = 0;
            begin = tmp;
            while (tmp && ft_strcmp(tmp->key, "word"))
            {
                len += ft_strlen(tmp->value);
                tmp = tmp->next;
            }
            tmp = begin;
            new_str = malloc(sizeof(char) * (len + 1));
            ft_bzero(new_str, len + 1);
            while (tmp && ft_strcmp(tmp->key, "word"))
            {
                ft_strlcat(new_str, tmp->value, len + 1);
                tmp = tmp->next;
            }
            if (begin == info->tokens)
            {
                info->tokens = lst_new(ft_strdup("word"), new_str);
                info->tokens->next = tmp;
            }
            else
            {
                prev->next = lst_new(ft_strdup("word"), new_str);
                prev->next->next = tmp;
           }
            
            while (begin && ft_strcmp(begin->key, "word"))
            {
                tmp = begin;
                begin = begin->next;
                lst_free_node(&tmp);
            }
            if (!begin)
                break;
            tmp = begin;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

static void remove_spaces(t_list **head)
{
    t_list *curr;
    t_list *prev;
    
    if (ft_strcmp((*head)->key, "space"))
    {
        curr = *head;
        *head = (*head)->next;
        lst_free_node(&curr);
    }
    if (!(*head))
        return ;
    prev = *head;
    curr = (*head)->next;
    while (curr)
    {
        if (ft_strcmp(curr->key, "space"))
        {
            prev->next = curr->next;
            lst_free_node(&curr);
            curr = prev->next;
            continue ;
        }
        prev = prev->next;
        curr = curr->next;
    }
}

static int is_redir(const char *str)
{
    if (ft_strcmp(str, "append") || ft_strcmp(str, "write") 
        || ft_strcmp(str, "heredoc") || ft_strcmp(str, "read"))
        return 1;
    return 0;
}

static int check_parsing(t_info *info)
{
    t_list *curr;
    t_list *next;
    
    if (!info->tokens)
        return 1;
    if (ft_strcmp(info->tokens->key, "pipe"))
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return 1;
    }
    curr = info->tokens;
    next = curr->next;
    while (curr)
    {
        if (!next)
        {
            if (!ft_strcmp(curr->key, "word"))
            {
                printf("minishell: syntax error near unexpected token `%s'\n", (char *)curr->value);
                return 1;
            }
            return 0;
        }
        if ((is_redir(curr->key) && !ft_strcmp(next->key, "word")) 
            || (ft_strcmp(curr->key, "pipe") && ft_strcmp(next->key, "pipe")))
        {
            printf("minishell: syntax error near unexpected token `%s'\n", (char *)next->value);
            return 1;
        }
        curr = next;
        next = next->next;
    }
    return 0;
}

static void create_grammemes(t_info *info)
{
    t_list *tmp;
    t_list *curr;
    t_list *key_tmp, value_tmp;
    
    curr = info->tokens;
    tmp = info->grammemes;
    while (curr)
    {
        lst_push_back(&tmp, lst_new(NULL, NULL));
        tmp->key = malloc(sizeof(t_list *));
        tmp->value = malloc(sizeof(t_list *));

        while (curr || !ft_strcmp(curr->key, "pipe"))
        {
            printf("check_gr\n");
            if (is_redir(curr->key))
            {
                lst_push_back(&((t_list *)tmp->value), lst_new(curr->key, curr->next->value));
                curr = curr->next->next;
            }
            else
            {
                lst_push_back((t_list **)tmp->key, lst_new(curr->key, curr->value));
                curr = curr->next;
            }
        }
    }
}

int parser(t_info *info)
{
    opening(info);
    merge(info);
    remove_spaces(&info->tokens);
    lst_print(info->tokens);
    if (check_parsing(info))
        return 1;
    create_grammemes(info);
    lst_print(((t_list *)(info->grammemes))->key);
    lst_print(((t_list *)(info->grammemes))->value);
 // add after creating grammemes foo
    //TODO check and fill grammar
    return 0;
}
