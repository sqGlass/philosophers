SRCS	= $(shell find . -name "*.c")
OBJS	= ${SRCS:.c=.o}
NAME	= philo_three
HEADER	= philo_header.h
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
all:	${NAME}
%.o: %.c ${HEADER}
		${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}
${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}
clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${NAME}
re:		fclean all
.PHONY:	re all clean fclean