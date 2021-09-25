CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f
NAME			= so_long
INCLUDES		= -I./includes
SRCS_PATH		= ./srcs/
LIBFT_PATH		= ./libft/
SRCS_FILES    	= $(SRCS_PATH)main.c
SRCS_OBJS		= ${SRCS_FILES:.c=.o}
LIBFTMAKE		= $(MAKE) -C ${LIBFT_PATH}
LIBFT			= -L$(LIBFT_PATH) -lft

all:			${NAME}

${NAME}:		${SRCS_OBJS} lib
				${CC} ${CFLAGS} ${INCLUDES} -o ${NAME} ${SRCS_OBJS} ${LIBFT}

lib:
				${LIBFTMAKE}

.c.o:
				$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
				$(LIBFTMAKE) clean
				${RM} ${SRCS_OBJS}

fclean:			clean
				$(LIBFTMAKE) fclean
				${RM} ${NAME} ${SRCS_PATH}${SRCS_OBJS}

re:				fclean all

.PHONY:			all clean fclean re