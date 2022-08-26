/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:48:01 by sshana            #+#    #+#             */
/*   Updated: 2022/08/25 09:55:57 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H

# define BUILT_INS_H

# include "structs.h"

//builtins
int			ft_env(t_info *info, t_list *grammeme);
int			ft_export(t_info *info, t_list *grammeme);
int			ft_unset(t_info *info, t_list *grammeme);
int			ft_exit(t_info *info, t_list *grammeme);
int			ft_echo(t_info *info, t_list *grammeme);
int			ft_cd(t_info *info, t_list *grammeme);
int			ft_pwd(t_info *info, t_list *grammeme);

#endif
