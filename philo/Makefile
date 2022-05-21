SRC = 				\
	atoui.c 		\
	free.c			\
	init.c			\
	main.c			\
	monitor.c		\
	philo_utils.c	\
	philo.c utils.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= philo
CFLAGS 		= -Wall -Werror -Wextra -O3
CPPFLAGS 	= -MMD

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
