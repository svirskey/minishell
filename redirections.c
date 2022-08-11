/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:15:18 by sshana            #+#    #+#             */
/*   Updated: 2022/08/10 09:35:27 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

int amount_of_file(t_list *tmp, int flag)
{
    int amount;

    amount = 0;
    while (tmp && ft_strcmp(tmp->key, "pipe") != 1)
    {
        if (flag == 0)
        {
            if ((ft_strcmp(tmp->key, "read") == 1) || (ft_strcmp(tmp->key, "heredoc") == 1))
                amount++;
        }
        else
        {
            if ((ft_strcmp(tmp->key, "write") == 1) || (ft_strcmp(tmp->key, "append") == 1))
                amount++;   
        }
        tmp = tmp->next;
    }
    return (amount);
}

void    cycle_gnl(char *limiter, int infd)
{
    char    *line;

    line = NULL;
    line = readline("here_doc> ");
    while (ft_strcmp(line, limiter) != 1)
    {
        if (line[0] == '\n')
            write(infd, "\n", 1);
        else
        {
            write(infd, line, ft_strlen(line));
            write(infd, "\n", 1);
        }
        free(line);
        line = readline("here_doc> ");
    }
    if (line)
        free(line);
    close(infd);
}

int here_doc(t_list *tmp)
{
    int infd;

    infd = open("minishell_heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (infd == -1)
        return (-1);
    cycle_gnl((char*)tmp->value, infd);
    infd = open("minishell_heredoc.txt", O_RDONLY, 0777);
    if (infd == -1)
        return (-1);
    return (infd);
}

static void    close_infile(int infd)
{
    if (infd > -1)
        close(infd);
}

int    check_infile(t_info *info, t_list *lst)
{
    int infd;
    t_list *tmp;

    tmp = *(t_list**)lst->value;
    infd = -1;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "read") == 1)
        {
            close_infile(infd);
            infd = open((char*)tmp->value, O_RDONLY, 0777);
            if (infd == -1)
                error_with_infile((char*)tmp->value, 0);
        }
        if (ft_strcmp(tmp->key, "heredoc") == 1)
        {
            close_infile(infd);
            infd = here_doc(tmp);
            if (infd == -1)
                error_with_infile("Error with open temporary files (heredoc).\n", 1);
        }
        tmp = tmp->next;
    }
    return (infd);
}

int    check_outfile(t_info *str, t_list *lst)
{
    t_list  *tmp;
    int outfd;

    tmp = *(t_list**)lst->value;
    outfd = -1;
    while (tmp)
    {
        if ((ft_strcmp(tmp->key, "write") == 1) || (ft_strcmp(tmp->key, "append") == 1))
        {
            if (outfd != -1)
                close(outfd);
            if (ft_strcmp(tmp->key, "write") == 1)
                outfd = open((char*)tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            else if (ft_strcmp(tmp->key, "append") == 1)
                outfd = open((char*)tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
            if (outfd == -1)
                return (error_with_outfile("minishell: error with output file.\n"));
        }
        tmp = tmp->next;
    }
    return (outfd);
}