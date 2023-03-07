NAME			= fdf

SRCS			= fdf.c fdf_utils.c fdf_parse.c fdf_graphic.c fdf_error.c fdf_graphic_utils.c

OBJS			= ${SRCS:.c=.o}

CC				= gcc

CFLAGS 			= -Wall -Werror -Wextra

BIGLIBFT		= ./big_Libft/

%.o:			%.c Makefile fdf.h
				${CC} ${CFLAGS} -O3 -c $< -o ${<:.c=.o}  -I./

${NAME}:		${OBJS} biglibft
				${CC} ${OBJS} big_Libft/libft.a big_Libft/printfd.a mlx/libmlx.a -lX11 -lXext -L./mlx/ -lm -g -o ${NAME}

all:			${NAME}

clean:
				rm -f ${OBJS}
				${MAKE} clean -C ${BIGLIBFT}

fclean:			clean
				rm -f ${NAME}
				${MAKE} fclean -C ${BIGLIBFT}

re:				fclean all

biglibft:		${BIGLIBFT}
				${MAKE} all -C ${BIGLIBFT}

.PHONY:			all clean fclean re biglibft
