CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
NAME			= so_long
INCLUDES		= includes
SRCS_PATH		= ./srcs/
LIBFT_PATH		= ./libft/
MLX_PATH		= ./mlx_linux/
SRCS_FILES    	= $(SRCS_PATH)main.c $(SRCS_PATH)utils.c $(SRCS_PATH)map_check.c $(SRCS_PATH)free.c $(SRCS_PATH)args_check.c $(SRCS_PATH)sl_utils.c $(SRCS_PATH)player_move.c $(SRCS_PATH)error_output.c
SRCS_OBJS		= $(SRCS_FILES:.c=.o)
LIBFTMAKE		= $(MAKE) -C $(LIBFT_PATH)
LIBFTFLAG		= -L$(LIBFT_PATH) -lft
MLXMAKE			= $(MAKE) -C $(MLX_PATH)
MLXFLAG			= -Lmlx_linux -lmlx -lXext -lX11 -lm -lbsd -Imlx_linux

all:			$(NAME)

$(NAME):		$(MLX_PATH) $(SRCS_OBJS) lib mlx
				$(CC) $(CFLAGS) $(SRCS_OBJS) $(LIBFTFLAG) $(MLXFLAG) -o $(NAME)

lib:
				$(LIBFTMAKE)

mlx:
				$(MLXMAKE)

.c.o:
				$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
				$(LIBFTMAKE) clean
				$(MLXMAKE) clean
				$(RM) $(SRCS_OBJS)

fclean:			clean
				$(LIBFTMAKE) fclean
				rm -f $(MLX_PATH)/libmlx.a
				$(RM) $(NAME) $(SRCS_PATH)$(SRCS_OBJS)

re:				fclean all

.PHONY:			all clean fclean re