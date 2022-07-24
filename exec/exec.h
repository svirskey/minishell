#ifndef EXEC_H
# define EXEC_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>



void	ft_free_execve_error(char **cmdargs, int flag);
void	ft_error_dup_bonus(int flaq);
void	ft_error_dup(pid_t pidl, int flag);
void	ft_error_pipe(void);
void	ft_error_fork(void);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *ch);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *line, char *buff);

#endif