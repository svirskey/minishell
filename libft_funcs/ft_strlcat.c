/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:21:55 by bfarm             #+#    #+#             */
/*   Updated: 2022/07/19 19:41:28 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (dst[size] && size <= dstsize)
		size++;
	while (size + i + 1 < dstsize && src[i])
	{
		dst[size + i] = src[i];
		i++;
	}
	if (size + i < dstsize)
		dst[size + i] = 0;
	if (size > dstsize || dstsize == 0)
		size = dstsize;
	i = 0;
	while (src[i])
	{
		size++;
		i++;
	}
	return (size);
}
