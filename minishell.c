/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/19 19:43:50 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static char	*ft_readline()
{
	char	*str;

	str = readline("minishell:");
	if (str && str[0] != 0)
		add_history(str);
	return (str);
}

static void ft_init(t_info *info, char **envp)
{
	info->envp_list = NULL;
	info->exit_status = 0;
	info->env_change = 0;
	info->builtins[0] = ft_strdup("echo");
	info->builtins[1] = ft_strdup("cd");
	info->builtins[2] = ft_strdup("pwd");
	info->builtins[3] = ft_strdup("export");
	info->builtins[4] = ft_strdup("unset");
	info->builtins[5] = ft_strdup("env");
	info->builtins[6] = ft_strdup("exit");
	env_init(info, envp);
}

static void ft_exit(t_info *info)
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
		lst_clear(&info.tokens);
		str = ft_readline(); 
		if (!str) // ctrl-d in empty line
			break;
		if (str[0] == 0)
		{
			free(str);
			continue;
		}
			

		lexer(&info, str);

		lst_print(info.tokens);

		parser(&info);
		// lexer = parsing input to grammar lexical units

		// parser = expansion and check for correct cases
		
		// executer
		
		free(str);
	}
	ft_exit(&info);
	return 0;
}
