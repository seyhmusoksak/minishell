NAME = minishell
SRCS = get_env.c minishell.c utils.c lexer/my_lexer.c parser/parser.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@make -C ./libft -s
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "              _       _      __         ____"
	@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
	@echo "  / __ \`__ \/ / __ \/ / ___/ __ \/ _ \/ / / "
	@echo " / / / / / / / / / / (__  ) / / /  __/ / /  "
	@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/   "
	@echo "Minishell is ready!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ./libft clean -s
	@rm -rf $(OBJS)
	@echo "Object files removed!"

fclean: clean
	@make -C ./libft fclean -s
	@rm -rf $(NAME)
	@echo "Program is removed!"

re: fclean all

.PHONY: all clean fclean re
