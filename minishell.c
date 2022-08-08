/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/08 21:47:30 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static char	*ft_readline()
{
	char	*str;

	str = readline("minishell$ ");
	if (str && str[0] != 0)
		add_history(str);
	return (str);
}

static foo_p *builtin_node(foo_p built_foo)
{
	 foo_p *node;

	 node = NULL;
	 node = malloc(sizeof(foo_p));
	 *node = built_foo;
	 return node;
}

static void ft_init(t_info *info, char **envp)
{
	info->envp_list = NULL;
	info->tokens = NULL;
	info->grammemes = NULL;
	info->envp_arr = NULL;
	info->builtins = NULL;
	info->exit_status = 0;
	info->envp_upd = 1;
	envp_init(info, envp);
	lst_push_back(&info->builtins, lst_new(ft_strdup("env"), builtin_node(&ft_env)));
	lst_push_back(&info->builtins, lst_new(ft_strdup("cd"), builtin_node(&ft_cd)));
	lst_push_back(&info->builtins, lst_new(ft_strdup("pwd"), builtin_node(&ft_pwd)));
	lst_push_back(&info->builtins, lst_new(ft_strdup("export"), builtin_node(&ft_export)));
	lst_push_back(&info->builtins, lst_new(ft_strdup("unset"), builtin_node(&ft_unset)));
	lst_push_back(&info->builtins, lst_new(ft_strdup("echo"), builtin_node(&ft_echo)));
	lst_push_back(&info->builtins, lst_new(ft_strdup("exit"), builtin_node(&ft_exit)));
}

static void ft_free_grammemes(t_info *info)
{
	t_list *tmp;
	
	tmp = info->grammemes;
	while (tmp)
	{
		lst_clear((t_list **)&tmp->key);
		lst_clear((t_list **)&tmp->value);
		tmp = tmp->next;
	}
	lst_clear(&info->grammemes);
}

void ft_free_info(t_info *info)
{
	lst_clear(&info->builtins);
	lst_clear(&info->envp_list);
	lst_clear(&info->tokens);
	ft_free_grammemes(info);
	lst_clear(&info->grammemes);
	envp_clear(&info->envp_arr);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_info info;
	char *str;

	ft_init(&info, envp);
	while(!info.exit_status)
	{
		str = ft_readline(); 
		if (!str) // ctrl-d in empty line
			break;
		if (str[0] == 0)
		{
			free(str);
			continue;
		}
		lexer(&info, str);
		parser(&info);
		// if (parser(&info)) //add after merging with executor
			// 	executor(info);

		lst_print_grammemes(info.grammemes);

		
		//(*(foo_p *)(info.builtins->value))(&info, info.tokens); // example of using builtin env
		
		ft_free_grammemes(&info);
		lst_clear(&info.tokens);
		free(str);
	}
	ft_free_info(&info);
	return 0;
}
