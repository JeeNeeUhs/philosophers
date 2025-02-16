CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

SRC_FILES = check.c \
			create.c \
			init.c \
			main.c \
			monitor.c \
			philo.c \
			utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re