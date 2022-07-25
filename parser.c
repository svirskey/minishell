

#include "minishell.h"
#include "structs.h"

// add separators between words for this case : 'e''c''h''o' == echo (correct)
// echo asd'asd  -> unclosed quotes are not interpretating
// echo $PWD != echo $P'W'D => read till spec symbol
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

    opn = NULL;
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
                free(tmp->key);
                free(tmp->value);
                free(tmp);
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
    new_str = NULL;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "word") && tmp->next && ft_strcmp(tmp->next->key, "word"))
        {
            
            len = 0;
            begin = tmp;
            while (ft_strcmp(tmp->key, "word"))
            {
                len += ft_strlen(tmp->value);
                tmp = tmp->next;
            }
            tmp = begin;
            new_str = malloc(sizeof(char) * (len + 1));
            ft_bzero(new_str, len + 1);
            while (ft_strcmp(tmp->key, "word"))
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
            while (ft_strcmp(begin->key, "word"))
            {
                tmp = begin;
                begin = begin->next;
                free(begin->key);
                free(begin->value);
                free(begin);
            }
        }

        prev = tmp;
        tmp = tmp->next;
        puts((char *)tmp->value);
    }
}

void parser(t_info *info)
{
    opening(info);
    puts("");
    lst_print(info->tokens);
    merge(info);
    
    // check grammar
    // creating list of grammar tokens united by highest priority token (pipe)
}
