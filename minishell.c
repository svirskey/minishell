/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 23:21:19 by bfarm            ###   ########.fr       */
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

static void ft_init(t_info *info, char **envp)
{
	info->envp_list = NULL;
	info->tokens = NULL;
	info->grammemes = NULL;
	info->envp_arr = NULL;
	info->exit_status = 0;
	info->envp_upd = 1;

	info->builtins[0] = ft_strdup("echo");
	info->builtins[1] = ft_strdup("cd");
	info->builtins[2] = ft_strdup("pwd");
	info->builtins[3] = ft_strdup("export");
	info->builtins[4] = ft_strdup("unset");
	info->builtins[5] = ft_strdup("env");
	info->builtins[6] = ft_strdup("exit");
	
	info->foo_ptrs[0] = &ft_echo;
	info->foo_ptrs[1] = &ft_cd;
	info->foo_ptrs[2] = &ft_pwd;
	info->foo_ptrs[3] = &ft_export;
	info->foo_ptrs[4] = &ft_unset;
	info->foo_ptrs[5] = &ft_env;
	info->foo_ptrs[6] = &ft_exit;
	envp_init(info, envp);
}

void ft_free_info(t_info *info)
{
	write(1,"\n",1);
	free(info->builtins[0]);
	free(info->builtins[1]);
	free(info->builtins[2]);
	free(info->builtins[3]);
	free(info->builtins[4]);
	free(info->builtins[5]);
	free(info->builtins[6]);
	lst_clear(&info->envp_list);
	lst_clear(&info->tokens);
	envp_clear(&info->envp_arr);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_info info;
	
	ft_init(&info, envp);
	char *str;

	str = NULL;
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
		// parser is :
		// check for correct grammar construction like  echo | | => incorrect 
		// fill grammar list of logical units like left and right parts of pipe

		//info.foo_ptrs[5](&info, info.tokens); // example of using builtin env
		
		
		// executer
		
		free(str);
	}
	ft_free_info(&info);
	return 0;
}
