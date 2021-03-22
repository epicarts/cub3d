cmake_minimum_required(VERSION 3.17)
project(cub3d)

set(CMAKE_C_STANDARD 11)

link_directories(./mlx)

add_executable(
        cub3d
        example/exam01.c
        cub3d.c cub3d.h)

target_link_libraries(cub3d "-framework AppKit" "-framework OpenGL" "mlx")
