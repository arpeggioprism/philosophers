NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo_bonus.c \
			check_bonus.c \
			allocation_bonus.c \
			threads_bonus.c \
			free_bonus.c
			
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
