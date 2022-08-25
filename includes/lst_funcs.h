/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:47:45 by sshana            #+#    #+#             */
/*   Updated: 2022/08/25 09:47:47 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_FUNCS_H

# define LST_FUNCS_H

typedef struct s_info	t_info;

typedef struct s_list	t_list;

typedef int				(*t_foo_p)(t_info *, t_list *);

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
	int		envp_status;

	t_list	*tokens;
	t_list	*grammemes;
	int		fd_in;
	int		fd_out;
	int		std_in;
	int		std_out;
	int		exit_status;
};

//list funcs
void		lst_pb(t_list **lst, t_list *node);
t_list		*lst_new(void *key, void *value);
void		lst_clear(t_list **lst);
void		lst_print(t_list *lst);
void		*lst_copy_value(t_list *lst, void *key);
char		*lst_get_value(t_list *lst, void *key);
void		lst_free_node(t_list **node);
void		lst_print_grammemes(t_list *grammemes);
int			lst_len(t_list *lst);
void		lst_replace(t_list *list, char *key, char *new_value);
void		lst_remove(t_list **head, t_list **del);
void		lst_remove_nodes(t_list **head, char *key);

#endif