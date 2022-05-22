SRC =				\
	finish_proc.c	\
	ft_atoi.c		\
	ft_itoa.c		\
	ft_strjoin.c	\
	main.c			\
	philo_actions.c	\
	philo.c			\
	sem_group.c		\
	utils.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME		= philo_bonus
CFLAGS		= -Wall -Werror -Wextra -O3
CPPFLAGS	= -MMD

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
