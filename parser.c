

#include "minishell.h"
#include "structs.h"

// add separators between words for this case : 'e''c''h''o' == echo (correct)
// echo asd'asd  -> unclosed quotes are not interpretating
// echo $PWD != echo $P'W'D => read till spec symbol
static void opening(t_info *info)
{

}

static void merge(t_info *info)
{
   
}

void parser(t_info *info)
{
    opening(info);
    merge(info);
    // check grammar
    // creating list of grammar tokens united by highest priority token (pipe)
}