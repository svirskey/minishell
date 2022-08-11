/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 19:34:43 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static char	*ft_readline(void)
{
	char	*str;

	str = readline("minishell$ ");
	if (str && str[0] != 0)
		add_history(str);
	return (str);
}

static t_foo_p	*builtin_node(t_foo_p built_foo)
{
	t_foo_p	*node;

	node = NULL;
	node = malloc(sizeof(t_foo_p));
	*node = built_foo;
	return (node);
}

static void	ft_init(t_info *info, char **envp)
{
	info->envp_list = NULL;
	info->tokens = NULL;
	info->grammemes = NULL;
	info->envp_arr = NULL;
	info->builtins = NULL;
	info->exit_status = 0;
	info->envp_upd = 1;
	envp_init(info, envp);
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("env"), builtin_node(&ft_env)));
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("cd"), builtin_node(&ft_cd)));
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("pwd"), builtin_node(&ft_pwd)));
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("export"), builtin_node(&ft_export)));
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("unset"), builtin_node(&ft_unset)));
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("echo"), builtin_node(&ft_echo)));
	lst_push_back(&info->builtins,
		lst_new(ft_strdup("exit"), builtin_node(&ft_exit)));
}

static void	ft_free_grammemes(t_info *info)
{
	t_list	*tmp;

	tmp = info->grammemes;
	while (tmp)
	{
		lst_clear((t_list **)tmp->key);
		lst_clear((t_list **)tmp->value);
		tmp = tmp->next;
	}
	lst_clear(&info->grammemes);
}

void	ft_free_info(t_info *info)
{
	lst_clear(&info->builtins);
	lst_clear(&info->envp_list);
	lst_clear(&info->tokens);
	ft_free_grammemes(info);
	envp_clear(&info->envp_arr);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*str;

	(void)argc;
	(void)argv;
	ft_init(&info, envp);
	while (!info.exit_status)
	{
		str = ft_readline();
		if (!str) //ctrl-d in empty line
			break ;
		if (str[0] == 0)
		{
			free(str);
			continue ;
		}
		lexer(&info, str);
		if (parser(&info))
			 	executor(&info);
		ft_free_grammemes(&info);
		lst_clear(&info.tokens);
		free(str);
	}
	ft_free_info(&info);
	return (0);
}

//ft_export(&info, *(t_list **)info.grammemes->key);	 // for  ( cd somepath | pwd ) command 
//ft_env(&info, *(t_list **)info.grammemes->next->key);

