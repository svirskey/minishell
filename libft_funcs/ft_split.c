/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:56 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/18 19:11:20 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

static int	count_strs(char const *s, char c)
{
	int	i;
	int	count_str;

	i = 0;
	count_str = 0;
	while (s[i])
	{
		if ((s[i] != c && !s[i + 1])
			|| (s[i] != c && s[i + 1] && s[i + 1] == c))
			count_str++;
		i++;
	}
	return (count_str);
}

static void	fill_strs(char *ret, char const *s, int *str_len, int *i)
{
	int	num_of_symb;

	num_of_symb = 0;
	while (num_of_symb < *str_len)
	{
		ret[num_of_symb] = s[*i];
		(*i)++;
		num_of_symb++;
	}
	ret[num_of_symb] = 0;
	*str_len = 0;
	(*i)--;
}

static int	check_null(char **ret, int *num_of_str, int str_len, int *j)
{
	int	i;

	(*j) -= str_len - 1;
	i = 0;
	ret[*num_of_str] = (char *)malloc(sizeof(char) * (str_len + 1));
	if (ret[*num_of_str] == NULL)
	{
		while (i < *num_of_str)
		{
			free(ret[i]);
			i++;
		}
		free(ret);
		return (0);
	}
	(*num_of_str)++;
	return (1);
}

static void	check_for_strs(char const *s, int i, char c, int *str_len)
{
	if (i == 0 && s[i] != c)
		*str_len = 1;
	else if (i > 0 && s[i - 1] == c && s[i] != c)
		*str_len = 1;
	else if (i > 0 && s[i - 1] != c && s[i] != c)
		(*str_len)++;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		num_of_str;
	int		str_len;
	char	**ret;

	if (s == NULL)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	num_of_str = 0;
	while (s[i])
	{
		check_for_strs(s, i, c, &str_len);
		if ((s[i] != c) && ((s[i + 1] && s[i + 1] == c) || (!s[i + 1])))
		{
			if (check_null(ret, &num_of_str, str_len, &i) == 0)
				return (NULL);
			fill_strs(ret[num_of_str - 1], s, &str_len, &i);
		}
		i++;
	}
	ret[count_strs(s, c)] = 0;
	return (ret);
}
