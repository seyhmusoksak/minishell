NAME = minishell
SRCS = exec.c get_env.c minishell.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline

SRCS = minishell.c get_env.c lexer/my_lexer.c utils.c exec.c \
		builtin/export.c builtin/pwd.c builtin/cd.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) $(SRCS)
	@make -C ./libft -s
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "              _       _      __         ____"
	@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
	@echo "  / __ \`__ \/ / __ \/ / ___/ __ \/ _ \/ / / "
	@echo " / / / / / / / / / / (__  ) / / /  __/ / /  "
	@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/   "
	@echo "Minishell is ready!"
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
.PHONY: all clean fclean re
