/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:54:59 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/10 18:55:15 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

static int	count_size(int n)
{
	int			size;
	long long	tmp;

	tmp = (long long)n;
	size = 0;
	if (n < 0)
	{
		size++;
		tmp *= -1;
	}
	if (n == 0)
		size = 1;
	while (tmp != 0)
	{
		tmp /= 10;
		size++;
	}
	return (size);
}

static void	reverse_str(char *str, int size, int sign, int k)
{
	int	i;
	int	tmp;

	if (sign)
		str[k] = '-';
	str[size] = 0;
	i = 0;
	while (i < size / 2)
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char		*ret;
	int			size;
	int			i;
	int			sign;
	long long	tmp;

	size = count_size(n);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	tmp = n;
	sign = 0;
	if (tmp < 0)
	{
		sign = 1;
		tmp *= -1;
	}
	while (++i < size - sign)
	{
		ret[i] = tmp % 10 + 48;
		tmp = tmp / 10;
	}
	reverse_str(ret, size, sign, i);
	return (ret);
}
