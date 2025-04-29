NAME = minishell
SOURCES = ./minishell.c \
					./parser/parser.c ./parser/parser_utils.c

OBJECTS = ./objects/minishell.o \
					./objects/parser.o ./objects/parser_utils.o

LIBFT = ./objects/libft.a

OBJDIR = ./objects

CC = cc
CCFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJDIR) $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(LDFLAGS) -o $@ $(CFLAGS)

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
