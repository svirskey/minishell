#ifndef LIBFT_FUNCS_H

# define LIBFT_FUNCS_H

#include <stdlib.h>

int			ft_strlen(char *s);
char		*ft_strdup(const char *s1);
char		*ft_substr(char *s, int start, int len);
int			ft_isspace(const char c);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char *s1, char *s2);
long long	ft_atol(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, int len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

# endif
