NAME = minishell

SRC = $(shell find . -name '*.c')

OBJS = ${patsubst %.c,%.o, ${SRC}}

HEADERS = minishell.h structs.h

CFLAGS = -Wall -Wextra -Werror

COMPILER = cc

all: ${NAME} 

${NAME}: $(OBJS)
	$(CC) $(OBJS) -lreadline -lncurses -o $@

%.o : %.c $(HEADERS) Makefile
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 
