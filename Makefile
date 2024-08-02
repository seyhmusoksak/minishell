NAME = minishell

SRCS = get_env.c minishell.c signal.c parser/parser.c parser/parser_utils.c \
		parser/parser_clean.c error_utils.c parser/quote_utils.c \
		parser/quote_check.c parser/put_env.c parser/put_env_utils.c \
		parser/dolar_check_utils.c  lexer/add_cluster.c \
		error/file_error.c   lexer/open_files.c  lexer/files_utils.c lexer/arg_utils.c \
		route.c builtin/cd.c builtin/error.c builtin/pwd.c  builtin/echo.c builtin/env.c builtin/export.c \
		builtin/unset.c  parser/united_dolar.c parser/redirect_right_parser.c \
		parser/redirect_left_parser.c parser/len_utils.c
		# lexer/lexer.c lexer/lexer_utils.c

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = gcc
READLINE_LIB_LOC = readline/lib
READLINE_INC_LOC = readline/include
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address -I $(READLINE_INC_LOC)
LDFLAGS = -L$(READLINE_LIB_LOC) -I$(READLINE_INC_LOC) -lreadline -lhistory

READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_DIR = readline-8.2
READLINE_ARCHIVE = readline-8.2.tar.gz
READLINE_TARGET = $(READLINE_LIB_LOC)/libreadline.a

all: $(READLINE_TARGET) $(NAME)

$(READLINE_TARGET):
	@echo "Updating readline library..."
	@curl -O $(READLINE_URL)
	@tar -xvf $(READLINE_ARCHIVE)
	@cd $(READLINE_DIR) && ./configure --prefix=${PWD}/readline && make && make install
	@echo "set echo-control-characters 0" > $(HOME)/.inputrc
	@rm -rf $(READLINE_DIR) $(READLINE_ARCHIVE)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "              _       _      __         ____"
	@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
	@echo "  / __ \`__ \/ / __ \/ / ___/ __ \/ _ \/ / / "
	@echo " / / / / / / / / / / (__  ) / / /  __/ / /  "
	@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/   "
	@echo "Minishell is ready!"

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean -s
	@rm -rf $(OBJS)
	@echo "Object files removed!"

fclean: clean
	@make -C $(LIBFT_DIR) fclean -s
	@rm -rf $(NAME)
	@rm -rf readline readline-8.2 readline-8.2.tar.gz
	@echo "Program is removed!"

re: fclean all

.PHONY: all clean fclean re
