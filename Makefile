CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBS   = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS = ./cub3d.c \
       ./utils/ft_strlcpy.c \
       ./utils/ft_split.c \
       ./utils/ft_strcmp.c \
       ./gnl/get_next_line.c \
       ./gnl/get_next_line_utils.c \
       ./utils/ft_atoi.c \
       ./utils/ft_isdigit.c \
       ./utils/free_2d_malloc.c \
       ./utils/digit_in_str.c \
       ./utils/is_map.c \
       ./utils/set_xy.c \
	./utils/ft_bzero.c \
       ./config/init_identifier_fc.c \
       ./config/init_identifier.c \
       ./config/init_identifier_texture.c \
       ./config/config.c \
       ./config/init_map.c \
       ./config/init_identifier_fc.c \
       ./config/init_identifier_r.c \
       ./config/check_utils.c \
       ./config/first_map_check.c \
       ./config/map_check_dfs.c \
       ./core/texture.c \
       ./core/ray.c \
       ./core/draw_wall.c \
       ./core/sprite_utils.c \
       ./core/sprite.c \
       ./core/init_sprite.c \
       ./core/draw_floor_ceiling.c \
       ./config/map_check.c \
       ./core/move.c \
       ./config/arg_parser.c \
       ./core/screenshot.c \
       ./core/hook_event.c \
       ./memory/exit_free.c \
       ./memory/exit_malloc.c

NAME = cub3D
CUBLIB = cub3d.a
HEADERS = cub3d.h

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(CUBLIB) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(CUBLIB) $(LIBS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME) $(CUBLIB)

re: fclean all

.PHONY:	all clean fclean re
