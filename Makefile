NAME = minishell
SOURCES = ./parser/parser.c \
		  ./parser/parser_utils.c

OBJECTS = ./objects/parser.o \
		  ./objects/parser_utils.o

LIBFT = ./objects/libft.a

CC = cc
CCFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) -o $@ $(CFLAGS)
$(LIBFT):
	make -C ./libft 
	cp ./libft/libft.a ./objects/

$(OBJECTS): $(SOURCES)
	mkdir -p objects
	$(CC) -c $^ $(CFLAGS)
	mv *.o ./objects/

clean:
	make -C ./libft clean
	rm -rf ./objects

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
