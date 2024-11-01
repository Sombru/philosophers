NAME = philosophers

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf

SRCS = main.c \
		errors.c \
		ft_usleep.c \
		init.c \
		manage_forks.c \
		parsing.c \
		threads.c \
		monitor.c \
		routine.c 


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "compiling philosophers..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "done"

clean: 
	@echo "cleaning up..."
	@$(RM) $(OBJS)
	@echo "done"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re