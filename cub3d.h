//
// Created by YoungHo on 2021/03/20.
//

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

#include "mlx/mlx.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17 //exit key code

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define KEY_LEFT			123
# define KEY_DOWN			125
# define KEY_RIGHT			124
# define KEY_UP				126



int		cub3d(int fd, char **line);


#endif
