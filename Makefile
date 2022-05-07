SRC = main.c ft_atoui.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= philo
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g
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
