NAME = minishell

YELLOW = \033[1;33m
PURPLE = \033[1;35m
WHITE = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
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
EXECUTE_FILENAMES = $(addprefix $(EXECUTE_DIR), execute_no_pipes execute_utils execute find_cmd handle_redirs)
INIT_FILNAMES = $(addprefix $(INIT_DIR), init_signals)
PARSER_FILNAMES = $(addprefix $(PARSER_DIR), assign_types assign_utils parser_utils parser syntax_check)

FILENAMES = $(MAIN_FILENAME) $(BUILTIN_FILENAMES) $(ENVIRONMENT_FILENAMES) $(EXECUTE_FILENAMES) $(INIT_FILNAMES) $(PARSER_FILNAMES)
SOURCES = $(addsuffix .c, $(FILENAMES))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(notdir $(FILENAMES))))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
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
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@make -sC libft

$(OBJECTS_DIR)%.o: %.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(BUILTINS_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(ENVIRONMENT_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(EXECUTE_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(INIT_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o: $(PARSER_DIR)%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJECTS_DIR)
	@make -sC libft clean

fclean: clean
	@rm -f $(NAME)
	@make -sC libft fclean

re: fclean all

.PHONY: all clean fclean re
