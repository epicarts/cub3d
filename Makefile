CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

#LIBS   = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm


SRCS = ./cub3d.c \



NAME = libftprintf.a
HEADERS = cub3d.h

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(HEADERS)


#gcc -L../mlx -lmlx -framework OpenGL -framework AppKit exam01.c

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re