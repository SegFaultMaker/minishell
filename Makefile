NAME = minishell

GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
WHITE = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
INCLUDES = -I. -Ilibft

OBJECTS_DIR = objs/

BUILTINS_DIR = builtins/
ENVIRONMENT_DIR = environment/
EXECUTE_DIR = execute/
INIT_DIR = init/
PARSER_DIR = parser/

MAIN_FILENAME = minishell
BUILTIN_FILENAMES = $(addprefix $(BUILTINS_DIR), cd echo env export_utils export pwd unset)
ENVIRONMENT_FILENAMES = $(addprefix $(ENVIRONMENT_DIR), convert_to_strings create delete hashing init operations resize utils)
EXECUTE_FILENAMES = $(addprefix $(EXECUTE_DIR), execute_no_pipes execute_utils execute find_cmd handle_redirs redir_operations env_vars)
INIT_FILNAMES = $(addprefix $(INIT_DIR), init_signals)
PARSER_FILNAMES = $(addprefix $(PARSER_DIR), assign_types assign_utils parser_utils parser syntax_check)

FILENAMES = $(MAIN_FILENAME) $(BUILTIN_FILENAMES) $(ENVIRONMENT_FILENAMES) $(EXECUTE_FILENAMES) $(INIT_FILNAMES) $(PARSER_FILNAMES)
SOURCES = $(addsuffix .c, $(FILENAMES))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(notdir $(FILENAMES))))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "$(BLUE)Compiling $@...$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)Done!$(WHITE)"
	@clear
	@echo "$(YELLOW)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo -n "$(PURPLE)"
	@echo "▌                            ▌               ▌   "
	@echo "▛▌▌▌  ▛▌▀▌▛▘▀▌▛▘▛▌▛▘▌▌  ▀▌▛▌▛▌  ▀▌▛▘▛▛▌▀▌▛▘▀▌▙▘█▌"
	@echo "▙▌▙▌  ▌▌█▌▄▌█▌▌ ▙▌▄▌▙▌  █▌▌▌▙▌  █▌▌ ▌▌▌█▌▌ █▌▛▖▙▖"
	@echo "  ▄▌            ▄▌  ▄▌                           "
	@echo "$(WHITE)"

$(LIBFT):
	@echo "$(BLUE)Compiling $@...$(WHITE)"
	@make -sC libft
	@echo "$(GREEN)Done!$(WHITE)"

$(OBJECTS_DIR)%.o: %.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(BLUE)Compiling $@$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(BUILTINS_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(BLUE)Compiling $@$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(ENVIRONMENT_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(BLUE)Compiling $@$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(EXECUTE_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(BLUE)Compiling $@$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(INIT_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(BLUE)Compiling $@$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(PARSER_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(BLUE)Compiling $@$(WHITE)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning minishell object files...$(WHITE)"
	@rm -rf $(OBJECTS_DIR)
	@echo "$(GREEN)Done!$(WHITE)"
	@echo "$(BLUE)Cleaning libft object files...$(WHITE)"
	@make -sC libft clean
	@echo "$(GREEN)Done!$(WHITE)"

fclean: clean
	@echo "$(BLUE)Deleting $(LIBFT)...$(WHITE)"
	@make -sC libft fclean
	@echo "$(GREEN)Done!$(WHITE)"
	@echo "$(BLUE)Deleting $(NAME)...$(WHITE)"
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(WHITE)"

re: fclean all

.PHONY: all clean fclean re
