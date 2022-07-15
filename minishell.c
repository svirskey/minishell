/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 21:46:25 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static char	*ft_readline()
{
	char	*str;

	str = readline("minishell:");
	if (str)
		add_history(str);
	return (str);
}

static void ft_init(t_info *info, char **envp)
{
	info->envp_list = NULL;
	info->exit_status = 0;
	info->env_change = 0;
	env_init(info, envp);
}

static void ft_exit(t_info *info)
{
	write(1,"\n",1);
	ft_list_clear_hard(&(info->envp_list));
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_info info;
	
	ft_init(&info, envp);
	char *str;

	//TODO: Sadd history 
	str = NULL;
	while(!info.exit_status)
	{
		str = ft_readline(); 
		if (!str) // ctrl-d in empty line
			break;
		if (str[0] == 0)
			continue;

		// lexer = parsing input to grammar lexical units
		// parser = getting lexema type and check for correct cases
		// executer
		
		free(str);
	}
	ft_exit(&info);
	return 0;
}
