# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 16:49:49 by pabad-ap          #+#    #+#              #
#    Updated: 2024/08/20 18:09:23 by pabad-ap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo 

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
THREAD_LINK =	-pthread

SRC 		=	main.c \
				ft_input_checker.c \
				ft_utils.c \
				ft_atoi.c \
				ft_errors.c \
				ft_init_data.c \
				ft_clean_data.c \
				ft_mutex_resources.c \
				ft_routine.c
OBJS_DIR	= ./build/
OBJS		= $(addprefix $(OBJS_DIR), $(patsubst %.c, %.o, $(SRC)))
				
HEADERS		= philo.h

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(THREAD_LINK) $(OBJS) -o $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c Makefile $(HEADERS) | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(THREAD_LINK) $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
