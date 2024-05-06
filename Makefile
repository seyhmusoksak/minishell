NAME = minishell
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LDFLAGS = -lreadline
SRCS = minishell.c get_env.c lexer/my_lexer.c utils.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
