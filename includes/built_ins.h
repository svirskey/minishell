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

# endif
