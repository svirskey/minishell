NAME = minishell

SRC	=	main/minishell.c												\
		main/ft_free.c					main/signals.c					\
		main/env_parse.c				main/envp_actions.c				\
		parser/lexer.c					parser/lexer_cases.c			\
		parser/opening.c				parser/merging.c				\
		parser/grammemes.c				parser/parser.c					\
		executor/executor.c				executor/redirections.c			\
		executor/execve_utils.c			executor/executor_pipe.c		\
		executor/heredoc.c				executor/error_print.c			\
		list_funcs/lst_change.c			list_funcs/lst_clear.c			\
		list_funcs/lst_get.c			list_funcs/lst_print.c			\
		built_ins/cd.c					built_ins/echo.c				\
		built_ins/env.c					built_ins/exit.c				\
		built_ins/export.c				built_ins/pwd.c					\
		built_ins/unset.c												\
		libft_funcs/ft_atol.c			libft_funcs/ft_bzero.c			\
		libft_funcs/ft_isspace.c		libft_funcs/ft_itoa.c			\
		libft_funcs/ft_split.c			libft_funcs/ft_strcmp.c			\
		libft_funcs/ft_strdup.c			libft_funcs/ft_strjoin.c		\
		libft_funcs/ft_strlcat.c		libft_funcs/ft_strlen.c			\
		libft_funcs/ft_strncmp.c		libft_funcs/ft_strnstr.c		\
		libft_funcs/ft_substr.c											

OBJS = $(patsubst %.c,%.o, $(SRC))

DEPS = $(patsubst %.c,%.d, $(SRC))

INCLUDE = ./includes

CFLAGS = -MMD -Wall -Wextra -Werror

COMPILER = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lreadline -lncurses -o $@

%.o : %.c
	$(CC)  $(CFLAGS) -c $< -o $@ -I$(INCLUDE)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re 
