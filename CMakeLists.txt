cmake_minimum_required(VERSION 3.17)
project(cub3d)

set(CMAKE_C_STANDARD 11)

link_directories(./mlx)

add_executable(
        cub3d
        cub3d.c cub3d.h
        utils/ft_strlcpy.c
        utils/ft_split.c
        utils/ft_strcmp.c
        gnl/get_next_line.c
        gnl/get_next_line_utils.c
        utils/ft_atoi.c
        utils/ft_isdigit.c
        utils/free_2d_malloc.c
        utils/digit_in_str.c
        utils/is_map.c
        utils/set_xy.c
        config/init_identifier_fc.c
        config/init_identifier.c
        config/init_identifier_texture.c
        config/config.c
        config/init_map.c
        config/init_identifier_fc.c
        config/init_identifier_r.c
        config/check_utils.c
        config/first_map_check.c
        core/texture.c
        core/ray.c
        core/draw_wall.c
        core/sprite.c
        core/init_sprite.c
        core/draw_floor_ceiling.c
        config/map_check.c
        core/move.c
        config/arg_parser.c
        core/screenshot.c
        utils/ft_bzero.c
        core/hook_event.c
        memory/exit_free.c
        memory/exit_malloc.c
        core/sprite_utils.c
        config/map_check_dfs.c
)

target_link_libraries(cub3d "-framework AppKit" "-framework OpenGL" "mlx")
