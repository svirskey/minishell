/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshana <sshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:11:17 by sshana            #+#    #+#             */
/*   Updated: 2022/07/24 18:30:05 by sshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_strjoin(char *line, char *buff)
{
	char	*str;
	int		i;
	int		j;

	if (!line || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(line) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		str[i] = line[i];
		i++;
	}
	while (buff[j] != '\0')
	{
		str[i] = buff[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
