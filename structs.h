/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:06 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/04 22:39:44 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

typedef struct s_info t_info;

typedef struct s_list t_list;

typedef int (*fp)(t_info *, t_list *);

struct s_list
{
	t_list	*next;
	void	*key;
	void	*value;
};

struct s_info
{
	char	*builtins[7];
	fp		foo_ptrs[7];

	t_list	*envp_list;
	char	**envp_arr;
	int		envp_upd;

	t_list	*tokens;
	t_list	*grammemes;

	int		exit_status;
};

//list funcs
void	lst_push_back(t_list **lst, t_list *node);
t_list	*lst_new(void *key, void *value);
void	lst_clear(t_list **lst);
void	lst_print(t_list *lst);
void	*lst_get_value(t_list *lst, void *key);
void	lst_free_node(t_list **node);

//libft funcs
int		ft_strlen(char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char *s, int start, int len);
int		ft_isspace(const char c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);

// envp funcs
void	envp_init(t_info *info, char **env);
void	envp_clear(char ***arr);
void	envp_update(t_info *info);

//main funcs
void	ft_free_info(t_info *info);
int		next_char(char *str, int begin, char origin);
void	lexer(t_info *info, char *str);
void	parser(t_info *info);

//builtins
int		ft_env(t_info *info, t_list *grammeme);
int		ft_export(t_info *info, t_list *grammeme);
int		ft_unset(t_info *info, t_list *grammeme);
int		ft_exit(t_info *info, t_list *grammeme);
int		ft_echo(t_info *info, t_list *grammeme);
int		ft_cd(t_info *info, t_list *grammeme);
int		ft_pwd(t_info *info, t_list *grammeme);
#endif