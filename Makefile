NAME		= philo

CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

BUILD_DIR	= build
SRCS		= main.c utils.c philo.c simulation.c
OBJS		= $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -g -fsanitize=thread $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CC) -g -fsanitize=thread $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re