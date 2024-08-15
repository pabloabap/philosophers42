# CABECERA!!
#
# pthread_create -> compile and link with -pthread.
#

NAME	= philo 

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
THREAD_LINK =	-pthread

OBJS 		=	main.o \
				ft_input_checker.o \
				ft_utils.o \
				ft_errors.o

HEADERS		= philo.h

all: $(NAME)

$(NAME) : $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(THREAD_LINK) $(OBJS) -o $(NAME)

$(OBJS): Makefile $(HEADERS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
