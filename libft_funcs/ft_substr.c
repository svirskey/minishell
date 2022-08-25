/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:21:49 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/25 14:39:35 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"
#include "structs.h"

static int	fill_arr(char const *s, char *ret, int len_to, int start)
{
	int	i;

	i = 0;
	while (i < len_to)
	{
		ret[i] = s[i + start];
		i++;
	}
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*ret;
	int		i;
	int		len_to;

	if (s == NULL)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	len_to = 0;
	if (ft_strlen(s) <= start)
	{
		ret = (char *)malloc(sizeof(char));
		if (!ret)
			malloc_err();
		ret[0] = 0;
		return (ret);
	}
	while (s[start + len_to] && len_to < len)
		len_to++;
	ret = (char *)malloc((len_to + 1) * sizeof(char));
	if (ret == NULL)
		malloc_err();
	i = fill_arr(s, ret, len_to, start);
	ret[i] = 0;
	return (ret);
}
