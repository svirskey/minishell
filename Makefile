NAME = minishell

SRC = ${wildcard *.c}

OBJS = ${patsubst %.c,%.o, ${SRC}}

HEADERS = minishell.h

CFLAGS = -Wall -Wextra -Werror

COMPILER = cc

all: ${NAME} 

${NAME}: $(OBJS)
	$(CC) $(OBJS) -lreadline -lncurses -o $@

%.o : %.c $(HEADERS) Makefile
	$(CC)  $(CFLAGS) -c $< 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 
