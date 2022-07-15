/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 21:14:01 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

static char	*ft_readline()
{
	char *str;
	str = NULL;
	str = readline("minishell: ");
	if (str)
		add_history(str);
	return (str);
}

static void ft_init(t_info *info, char **envp)
{
	info->envp_list = NULL;
	env_init(info, envp);
}

static void ft_exit(t_info *info)
{
	ft_list_clear(&(info->envp_list));
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_info info;
	
	ft_init(&info, envp);
	char *str;
	// add readline library
	// envp_list for key-value of envp
	// envp will be copied in envp_list
	// add history and arrow up to prev command
	str = NULL;
	while(/*not exit*/ 1)
	{
		str = ft_readline(); // todo, doesnt work
		if (str[0] == 0)
			continue;
		
		
		//
		// lexer = parsing input to grammar lexical units
		// parser = getting lexema type and check for correct cases
		// executer
		
		free(str);
	}

	ft_exit(&info);
	return 0;
}
