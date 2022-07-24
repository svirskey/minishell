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

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

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
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

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
	int	i;
	int	len_to;

	if (s == NULL)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	len_to = 0;
	if (ft_strlen(s) <= start)
	{
		ret = (char *)malloc(sizeof(char));
		ret[0] = 0;
		return (ret);
	}
	while (s[start + len_to] && len_to < len)
		len_to++;
	ret = (char *)malloc((len_to + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = fill_arr(s, ret, len_to, start);
	ret[i] = 0;
	return (ret);
}

int	ft_isspace(const char c)
{
	if (c == '\r' || c == '\n' || c == '\t' || c == ' ' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (0);
		else if (s1[i] < s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

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