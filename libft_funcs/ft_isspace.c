int	ft_isspace(const char c)
{
	if (c == '\r' || c == '\n' || c == '\t' || c == ' ' || c == '\f' || c == '\v')
		return (1);
	return (0);
}