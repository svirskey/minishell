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