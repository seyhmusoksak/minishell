NAME = minishell
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
SRCS = minishell.c get_env.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
