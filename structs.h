/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:06 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/15 21:01:22 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_info t_info;

typedef struct s_list t_list;

struct s_list
{
	t_list *next;
	char *key;
	char *value;
};

struct s_info
{
	t_list *envp_list;
	t_list *tokens;
	int exit_status;
	int env_change;
};

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *key, char *value);
void	ft_list_clear(t_list **lst);

int		ft_strlen(char *s);
void	env_init(t_info *info, char **env);