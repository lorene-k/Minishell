# ---------------- COLORS ---------------------------------------------------- #
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE			=	\033[0;38;5;208m
DEFAULT			=	\033[0m

# ---------------- PROJECT --------------------------------------------------- #
NAME			=	minishell

# ---------------- DIRECTORIES ----------------------------------------------- #
SRC_DIR			=	src/
INC_DIR			=	include/
OBJ_DIR			=	obj/
LIBFT_DIR		=	libft/

# ---------------- SOURCES -------------------------------------------------- #
SRCS			=	main.c \
					parsing/parsing.c \
					errors/free.c \
					execution/create_fd.c execution/execution.c execution/child.c  execution/create_pipes.c \
					builtin/pwd.c builtin/utils.c builtin/echo.c builtin/env.c builtin/export.c builtin/unset.c builtin/cd.c builtin/exit.c \
					parsing/create_commands.c parsing/set_file_type.c parsing/set_cmd_path.c \
					free/free_infos.c free/free_create_commands.c \
					tokenizer/token_nodes.c tokenizer/token_operators.c tokenizer/token_utils.c tokenizer/token_values.c tokenizer/tokens.c tokenizer/token_check.c \
					signals/signals.c signals/signals_heredoc.c errors/error.c \
					env/remove_vars.c env/env_var_utils.c env/expansion.c env/replace_vars.c env/env_var_update.c \
					parsing/check_redirects.c parsing/modify_args.c parsing/remove_quotes.c parsing/init_cmds.c parsing/handle_heredoc.c parsing/parsing_infos.c \
					builtin/export_content.c builtin/export_var.c parsing/remove_redirects.c parsing/set_path_resolution.c

SRCS			:=	$(addprefix $(SRC_DIR), $(SRCS))
OBJS			:=	$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# ---------------- COMPILATION ----------------------------------------------- #
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g
INCLUDES		=	-I$(INC_DIR) -I$(LIBFT_DIR)

# ---------------- RULES ----------------------------------------------------- #
all:			libft $(NAME)

libft:
				@make -C $(LIBFT_DIR)
				@cp $(LIBFT_DIR)libft.a ./

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft.a
				@echo "$(GREEN)Compiled $(NAME).$(DEFAULT)"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
				@make clean -C $(LIBFT_DIR)
				@rm -rf $(OBJ_DIR)
				@echo "$(ORANGE)Cleaned object files.$(DEFAULT)"

fclean:			clean
				@rm -f $(NAME) libft.a
				@echo "$(RED)Fully cleaned $(NAME) and libft.a.$(DEFAULT)"

re:				fclean all

.PHONY:			all clean fclean re libft