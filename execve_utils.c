/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:42:29 by sshana            #+#    #+#             */
/*   Updated: 2022/08/18 19:34:08 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

void	ft_free_cmdargs(char **cmdargs)
{
	int	i;

	i = 0;
	if (!cmdargs)
		return ;
	while (cmdargs[i])
	{
		free(cmdargs[i]);
		i++;
	}
	free(cmdargs);
}

char	**create_cmd_array(t_list *lst)
{
	t_list	*words;
	char	**cmd_line;
	int		num;
	int		len;

	words = *(t_list **)lst->key;
	num = lst_len(words);
	cmd_line = (char **)malloc(sizeof(char *) * (num + 1));
	num = 0;
	while (words)
	{
		cmd_line[num] = (char *)malloc(ft_strlen((char *)words->value) + 1);
		len = 0;
		while (((char *)words->value)[len])
		{
			cmd_line[num][len] = ((char *)words->value)[len];
			len++;
		}
		cmd_line[num][len] = '\0';
		num++;
		words = words->next;
	}
	cmd_line[num] = NULL;
	return (cmd_line);
}

static void	ft_free_paths_from_envp(char **paths_from_envp)
{
	int	i;

	i = 0;
	while (paths_from_envp[i])
	{
		free(paths_from_envp[i]);
		i++;
	}
	free(paths_from_envp);
}

static char	*ft_check_access(char **paths_from_envp, char *cmdargs)
{
	int		i;
	char	*path;
	char	*one_path;

	i = 0;
	while (paths_from_envp[i])
	{
		one_path = ft_strjoin(paths_from_envp[i], "/");
		path = ft_strjoin(one_path, cmdargs);
		free(one_path);
		if (access(path, F_OK) == 0)
		{
			ft_free_paths_from_envp(paths_from_envp);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_paths_from_envp(paths_from_envp);
	return (0);
}

char	*check_all_path(char **cmdargs, char **envp)
{
	char	*path;
	char	**paths_from_envp;
	char	*path_string;
	int		i;

	if (access(cmdargs[0], F_OK) == 0)
		return (cmdargs[0]);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	path_string = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!path_string)
		return (0);
	paths_from_envp = ft_split(path_string, ':');
	free(path_string);
	if (!paths_from_envp)
		return (0);
	path = ft_check_access(paths_from_envp, cmdargs[0]);
	if (!path)
		return (0);
	free(cmdargs[0]);
	cmdargs[0] = path;
	return (path);
}
