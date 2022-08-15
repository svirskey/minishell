/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:06 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/12 20:17:36 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

typedef struct s_info	t_info;

typedef struct s_list	t_list;

typedef int				(*t_foo_p)(t_info *, t_list *);

enum
{
	PROMPT,
	EXEC,
	EXIT
};

struct s_list
{
	t_list	*next;
	void	*key;
	void	*value;
};

struct s_info
{
	t_list	*builtins;

	t_list	*envp_list;
	char	**envp_arr;
	int		envp_upd;

	t_list	*tokens;
	t_list	*grammemes;
	int		fd_in; // why
	int		fd_out;
	int		std_in;
	int		std_out;
	int		exit_status;
};

//list funcs
void		lst_push_back(t_list **lst, t_list *node);
t_list		*lst_new(void *key, void *value);
void		lst_clear(t_list **lst);
void		lst_print(t_list *lst);
void		*lst_copy_value(t_list *lst, void *key);
char		*lst_get_value(t_list *lst, void *key);
void		lst_free_node(t_list **node);
void		lst_print_grammemes(t_list *grammemes);
int			lst_len(t_list *lst);
void		lst_replace(t_list *list, char *key, char *new_value);
void		lst_remove_node(t_list **head, char *key);

//libft funcs
int			ft_strlen(char *s);
char		*ft_strdup(const char *s1);
char		*ft_substr(char *s, int start, int len);
int			ft_isspace(const char c);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char *s1, char *s2);
long long	ft_atol(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, int len);
// envp funcs
void		envp_init(t_info *info, char **env);
void		envp_clear(char ***arr);
void		envp_update(t_info *info);
void		env_parse(char **arr, char *str);

//main funcs
void		ft_free_info(t_info *info);
int			next_char(char *str, int begin, char origin);
void		lexer(t_info *info, char *str);
int			parser(t_info *info);
void		executor(t_info *info);
void		ft_signals(t_info *info, int sig);

//builtins
int			ft_env(t_info *info, t_list *grammeme);
int			ft_export(t_info *info, t_list *grammeme);
int			ft_unset(t_info *info, t_list *grammeme);
int			ft_exit(t_info *info, t_list *grammeme);
int			ft_echo(t_info *info, t_list *grammeme);
int			ft_cd(t_info *info, t_list *grammeme);
int			ft_pwd(t_info *info, t_list *grammeme);

//utils for execve (massive cmd, envp, check path, check bin-command)
char	**make_massive_command(t_list *lst);
char	*check_all_path(char **cmdargs, char **envp);

//free massive for execve - if perror/exit(1)
void    ft_free_cmdargs(char **cmdargs);

//redir
int    check_infile(t_list *lst, t_info *info);
int    check_outfile(t_list *lst);

//error
int error_with_infile(char *message, int flag);
int error_with_outfile(char *message);

#endif