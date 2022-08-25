/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:47 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 16:35:44 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "libft_funcs.h"
#include "built_ins.h"

t_signals	g_sig;

static char	*ft_readline(void)
{
	char	*str;

	str = readline("minishell$ ");
	if (str && str[0] != 0)
		add_history(str);
	return (str);
}

static t_foo_p	*b_node(t_foo_p built_foo)
{
	t_foo_p	*node;

	node = NULL;
	node = malloc(sizeof(t_foo_p));
	if (!node)
		malloc_err();
	*node = built_foo;
	return (node);
}

static void	ft_init(t_info *info, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	info->envp_list = NULL;
	info->tokens = NULL;
	info->grammemes = NULL;
	info->envp_arr = NULL;
	info->builtins = NULL;
	info->exit_status = 0;
	info->envp_status = KO;
	info->fd_in = 0;
	info->fd_out = 1;
	info->std_in = dup(STDIN_FILENO);
	info->std_out = dup(STDOUT_FILENO);
	envp_init(info, envp);
	lst_pb(&info->builtins, lst_new(ft_strdup("env"), b_node(&ft_env)));
	lst_pb(&info->builtins, lst_new(ft_strdup("cd"), b_node(&ft_cd)));
	lst_pb(&info->builtins, lst_new(ft_strdup("pwd"), b_node(&ft_pwd)));
	lst_pb(&info->builtins, lst_new(ft_strdup("export"), b_node(&ft_export)));
	lst_pb(&info->builtins, lst_new(ft_strdup("unset"), b_node(&ft_unset)));
	lst_pb(&info->builtins, lst_new(ft_strdup("echo"), b_node(&ft_echo)));
	lst_pb(&info->builtins, lst_new(ft_strdup("exit"), b_node(&ft_exit)));
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*str;

	ft_init(&info, envp, argc, argv);
	while (true)
	{
		g_sig.is_quit = 0;
		ft_signals(&info, PROMPT);
		str = ft_readline();
		if (!str)
			ft_signals(&info, EXIT);
		if (str[0] == 0)
		{
			free(str);
			continue ;
		}
		lexer(&info, str);
		if (parser(&info) == 0)
			executor(&info);
		ft_free_grammemes(&info);
		lst_clear(&info.tokens);
		free(str);
	}
	ft_free_info(&info);
	return (0);
}
