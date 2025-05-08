NAME = minishell
SOURCES = ./minishell.c \
					./parser/parser.c ./parser/parser_utils.c \
					./parser/assign_types.c ./parser/assign_utils.c \
					./parser/syntax_check.c \
					./builtins/echo.c ./builtins/cd.c ./builtins/pwd.c \
					./init/init.c

OBJECTS = ./objects/minishell.o \
					./objects/parser.o ./objects/parser_utils.o \
					./objects/assign_types.o ./objects/assign_utils.o \
					./objects/syntax_check.o \
					./objects/echo.o ./objects/cd.o ./objects/pwd.o \
					./objects/init.o

LIBFT = ./objects/libft.a

OBJDIR = ./objects

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJDIR) $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(LDFLAGS) -o $@ 
$(OBJDIR):
	mkdir -p objects

$(LIBFT):
	make -C ./libft 
	cp ./libft/libft.a ./objects/

$(OBJECTS): $(SOURCES)
	$(CC) -c $^ $(CFLAGS)
	mv *.o ./objects/

clean:
	make -C ./libft clean
	rm -rf ./objects

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
