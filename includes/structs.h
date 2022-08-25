/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:06 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 09:44:16 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include "lst_funcs.h"

enum
{
	DOLLAR,
	BOTH
};

enum
{
	ENV,
	EXPORT,
	KO
};

enum
{
	PIPE,
	HEREDOC,
	READ,
	APPEND,
	WRITE
};

enum
{
	PROMPT,
	EXEC,
	EXIT,
	HERE
};

//lexer funcs
int			next_char(char *str, int begin, char origin);
void		lexer_word(t_info *info, char *str, int *i);
void		lexer_space(t_info *info, char *str, int *i);
void		lexer_spec(t_info *info, char *str, int *i);
void		lexer_quotes(t_info *info, char *str, int *i);

// envp funcs
void		envp_init(t_info *info, char **env);
void		envp_clear(char ***arr);
void		envp_update(t_info *info, int flag);
void		env_parse(char **arr, char *str);

//lexer and parser
void		lexer(t_info *info, char *str);
void		inner_open(t_info *info, t_list **prev, t_list **tmp);
void		merge(t_info *info);
int			is_redir(const char *str);
void		create_grammemes(t_info *info);
int			parser(t_info *info);

//executor
int			ft_exec(t_info *info, t_list *lst);
void		pipe_process(t_info *info, t_list *lst);
void		executor(t_info *info);

//other funcs
void		ft_signals(t_info *info, int sig);
void		p_err(char *str);
void		ft_free_grammemes(t_info *info);
void		ft_free_info(t_info *info);

//utils for execve 
char		**create_cmd_array(t_list *lst);
char		*check_all_path(char **cmdargs, char **envp);
void		ft_free_cmdargs(char **cmdargs);

//redir
int			here_doc(char *heredoc, t_info *info);
int			check_infile(t_list *lst, t_info *info);
int			check_outfile(t_list *lst, t_info *info);

int			error_files(char *path, int flag);
void		p_err_three(char *line, char *line2, char *line3);
void		bash_error_output(char *fpath, t_info *info, char **cmdargs);

#endif