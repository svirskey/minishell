

#include "minishell.h"
#include "structs.h"

// add separators between words for this case : 'e''c''h''o' == echo (correct)
// echo asd'asd  -> unclosed quotes are not interpretating
// echo $PWD != echo $P'W'D => read till spec symbol

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
        if ((ft_strcmp(tmp->key, "dquote") || ft_strcmp(tmp->key, "word")))
        {
            if (next_char(tmp->value, 0, '$') == -1)
            {
                free(tmp->key);
                tmp->key = ft_strdup("word");
            }
            else
            {
                i = next_char(tmp->value, 0, '$');
                printf("%d\n", i);
                lst_push_back(&opn, lst_new(ft_strdup("word"), ft_substr(tmp->value, 0, i)));
                i++;
                while (next_char(tmp->value, i, '$') != -1)
                {
                    if (((char *)tmp->value)[i] == '$')
                    {
                        //TODO
                        i++;
                    }
                    else if (((char *)tmp->value)[i] == '?')
                    {
                        //TODO
                    }
                    else
                        lst_push_back(&opn, lst_new(ft_strdup("word"), lst_get_value(info->envp_list, ft_substr(tmp->value, i, (next_char(tmp->value, i, '$'))))));
                    i += next_char(tmp->value, i, '$') + 1;
                }
                if (((char *)tmp->value)[i - 2] && ((char *)tmp->value)[i - 2] != '$' && ((char *)tmp->value)[i - 1] == '$')
                    lst_push_back(&opn, lst_new(ft_strdup("word"),ft_strdup("$")));
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

// static void merge(t_info *info)
// {
//    (void)info;
// }

void parser(t_info *info)
{
    opening(info);
    //merge(info);
    // check grammar
    // creating list of grammar tokens united by highest priority token (pipe)
}