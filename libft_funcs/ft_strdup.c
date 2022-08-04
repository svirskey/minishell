
#include <stdlib.h>

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