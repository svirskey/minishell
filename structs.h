/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:06 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 22:26:58 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_info t_info;

typedef struct s_list t_list;

enum tokens
{
	separator, // space ; < > << >>  кавычки
	word,
	singles, // ' '
	doubles, // " "
	redir_left, // <
	redir_right, // >
	double_left, // <<
	double_right, // >>
	pipe // |
};
// echo $aasdadad 123 = [123]
// echo "" 123 = [ 123]

struct s_list
{
	t_list *next;
	void *key;
	void *value;
};

struct s_info
{
	t_list *envp_list;
	t_list *tokens;
	int exit_status;
	int env_change;
	//TODO more info data
};

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *key, void *value);
void	ft_list_clear(t_list **lst); // clear only nodes
void	ft_list_clear_hard(t_list **lst); // clear with contents

int		ft_strlen(char *s);
void	env_init(t_info *info, char **env);

void ft_env(t_info *info);