/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:31:41 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:39:26 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"
#include "structs.h"

static void	fill_first(char const *s1, char *ret, int *i)
{
	while (s1[*i])
	{
		ret[*i] = s1[*i];
		(*i)++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	len = (int)ft_strlen(s1);
	len += (int)ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		malloc_err();
	fill_first(s1, ret, &i);
	len = i;
	i = 0;
	while (s2[i])
	{
		ret[len + i] = s2[i];
		i++;
	}
	ret[len + i] = 0;
	return (ret);
}
