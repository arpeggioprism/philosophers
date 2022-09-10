NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c \
			check.c \
			allocation.c \
			threads.c \
			free.c

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
