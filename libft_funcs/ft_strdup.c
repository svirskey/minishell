/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:21:38 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:39:17 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*ret;

	size = 0;
	while (s1[size])
		size++;
	ret = (char *)malloc((size + 1) * (sizeof(char)));
	if (ret == NULL)
		malloc_err();
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
