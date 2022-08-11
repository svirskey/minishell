/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:23:23 by sshana            #+#    #+#             */
/*   Updated: 2022/08/10 09:34:15 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

int error_with_infile(char *message, int flag)
{
    if (flag == 0)
        printf("minishell: %s: Not file or direction (or problem with file).\n", message);
    if (flag == 1)
        printf("%s", message);
    exit (1);
}

int error_with_outfile(char *message)
{
    printf("%s", message);
    return (-1);
}