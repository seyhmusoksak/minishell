NAME = minishell
SRCS =	UTILS/get_env.c minishell.c UTILS/signal.c PARSER/parser.c PARSER/parser_utils.c \
		PARSER/parser_clean.c ERROR/error_utils.c PARSER/quote_utils.c \
		PARSER/quote_check.c PARSER/put_env.c PARSER/put_env_utils.c \
		PARSER/dolar_check_utils.c  LEXER/add_cluster.c \
		ERROR/error_utils_2.c  LEXER/open_files.c  LEXER/files_utils.c LEXER/arg_utils.c \
		UTILS/route.c BUILTIN/cd.c BUILTIN/error.c BUILTIN/pwd.c  BUILTIN/echo.c BUILTIN/env.c BUILTIN/export.c \
		BUILTIN/unset.c  PARSER/united_dolar.c PARSER/redirect_right_parser.c \
		PARSER/redirect_left_parser.c PARSER/len_utils.c EXECUTOR/exec.c EXECUTOR/exec_utils.c \
		PARSER/char_control.c GNL/get_next_line.c LEXER/free_cluster.c LEXER/heredoc.c PARSER/node_utils.c \
		PARSER/pipe_utils.c  BUILTIN/exit.c PARSER/free_utils.c PARSER/tilda_check.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./INCLUDES/libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = gcc
READLINE_LIB_LOC = readline/lib
READLINE_INC_LOC = readline/include
CFLAGS = -g -Wall -Wextra -Werror -I $(READLINE_INC_LOC) -fsanitize=address
LDFLAGS = -L$(READLINE_LIB_LOC) -I$(READLINE_INC_LOC) -lreadline -lhistory -lncurses
READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_DIR = readline-8.2
READLINE_ARCHIVE = readline-8.2.tar.gz
all: $(READLINE_LIB_LOC)/libreadline.a $(NAME)
# Readline kütüphanesi kurulumu
$(READLINE_LIB_LOC)/libreadline.a: progress_bar.sh
	@clear
	@echo "\033[1;31mCompiling readline please wait...\n\033[0m"
	@echo "\033[1;30mDownloading readline...\033[0m"
	@bash progress_bar.sh
	@curl -s -O $(READLINE_URL)
	@echo "\033[1;30mRedline file extracting...\033[0m"
	@tar -xvf $(READLINE_ARCHIVE) 2>&1 | bash progress_bar.sh & wait
	@echo "\033[1;30mReadline extracted!\033[0m"
	@cd $(READLINE_DIR) && ./configure --prefix=${PWD}/readline 2>&1 | awk '{printf ""; fflush()}' & bash progress_bar.sh & wait
	@echo "\033[1;30mReadline configuration!\033[0m"
	@cd $(READLINE_DIR) && make install 2>&1 | awk '{printf ""; fflush()}' & bash progress_bar.sh & wait
	@wait
	@echo "\n\033[0;42mReadline installation completed!\033[0m"
	@rm -rf $(READLINE_ARCHIVE) $(READLINE_DIR)
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "\033[0;32m"
	@echo "              _       _      __         ____"
	@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
	@echo "  / __ \`__ \/ / __ \/ / ___/ __ \/ _ \/ / / "
	@echo " / / / / / / / / / / (__  ) / / /  __/ / /  "
	@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/   "
	@echo "\033[0m"
	@echo "\033[4;33mMinishell is ready!\033[0m"
$(LIBFT):
	@make -C $(LIBFT_DIR)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@make -C $(LIBFT_DIR) clean -s
	@rm -rf $(OBJS)
	@echo "\033[4;33mObject files removed!\033[0m"
fclean: clean
	@make -C $(LIBFT_DIR) fclean -s
	@rm -rf $(NAME)
	@rm -rf readline readline-8.2 readline-8.2.tar.gz
	@echo "\033[4;33mProgram is removed!\033[0m"
re: fclean all
.PHONY: all clean fclean re
