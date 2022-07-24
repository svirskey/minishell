/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:06 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/19 19:43:14 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_info t_info;

typedef struct s_list t_list;

enum free_type
{
	hard, // with key and value
	soft // only value
};

// enum tokens
// {
// 	separator, // space tab < > << >> | ' ""
// 	word,
// 	singles, // ' '
// 	doubles, // " "
// 	single_left, // < redirect input
// 	single_right, // > redirect output
// 	double_left, // << here-document with stop-word
// 	double_right, // >> redirect output in append mode
// 	pipe_token // |
// };
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
	char* builtins[7];
	t_list *envp_list;
	t_list *tokens;
	t_list *grammars; // list of grammar tokens united by highest priority token (pipe)
	int exit_status;
	int env_change;
	//TODO more info data
};

void	lst_push_back(t_list **lst, t_list *node);
t_list	*lst_new(void *key, void *value);
void	lst_clear(t_list **lst);
void	lst_print(t_list *lst);
void	*lst_get_value(t_list *lst, void *key);

int		ft_strlen(char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, int start, int len);
void	env_init(t_info *info, char **env);
int		ft_isspace(const char c);
int		ft_strcmp(const char *s1, const char *s2);

int		next_char(char *str, int begin, char origin);
void	lexer(t_info *info, char *str);
int		ft_env(t_info *info);