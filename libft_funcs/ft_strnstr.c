/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:34:16 by sshana            #+#    #+#             */
/*   Updated: 2022/08/18 19:11:03 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	j;
	int	needle_len;

	needle_len = ft_strlen((char *)needle);
	if (needle_len == 0)
		return ((char *)(haystack));
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && i + j < len && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
