//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <string.h>
//#include "../mlx/mlx.h"
//
//#define X_EVENT_KEY_PRESS		2
//#define X_EVENT_KEY_EXIT		17 //Exit program key code
//
//#define KEY_ESC			53
//
//# define TILE_SIZE 60
//# define ROWS 11
//# define COLS 15
//# define WIDTH COLS * TILE_SIZE
//# define HEIGHT ROWS * TILE_SIZE
//
//# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))
//
//typedef struct	s_img
//{
//	void	*img;
//	int		*data;
//
//	int		size_l;
//	int		bpp;
//	int		endian;
//}				t_img;
//
//typedef struct	s_game
//{
//	void	*mlx;
//	void	*win;
//	t_img	img;
//
//	int		map[ROWS][COLS];
//}				t_game;
//
////Draw the line by DDA algorithm
//void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
//{
//	double	deltaX;
//	double	deltaY;
//	double	step;
//
//	deltaX = x2 - x1; // x기울기. 끝점과 시작했을때 증가량
//	deltaY = y2 - y1; // y기울기. 끝점과 시작했을때 증가
//
//	//x의 움직임 > y의 움직임 . x가 더 많이 움직엿으면 x를 절대값 step . y가 많이 움직엿으면 y를 절대 값.
//	// x와 y의 거리. 증가량을 비교해서 더 큰게 기준축이 됨.
//	// y가 더 증가하면 증가폭이 크므로  / x가 더 증가폭이 크면,
//	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY); // 절대값
//
//	deltaX /= step; // deltax가 5이고, step이 5면, x축 증가량은 1
//	deltaY /= step; // deltay의 길이가 2이면, 기준축은 x,  y의 증가값은 2/5가 나옴.
////	printf("%f %f\n", deltaX, deltaY);
//	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01) // x2 - x1
//	{
//		// ((int)floor(Y) * WIDTH + (int)floor(X)) => 내림.
//		game->img.data[TO_COORD(x1, y1)] = 0xb3b3b3; // 반올림해서 해당 배열의 색을 바꿔줌.
//		printf("%f %f\n", x1, y1);
//		x1 += deltaX; // x축 기준이라면 1씩 증가함.
//		y1 += deltaY; // y는 y값에 증가량을 더해줌.
//	}
//}
//
//void 	draw_lines(t_game *game)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	while (i < COLS)
//	{
//		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
//		i++;
//	}
//	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
//	j = 0;
//	while (j < ROWS)
//	{
//		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
//		j++;
//	}
//	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
//}
//
//void	draw_rectangle(t_game *game, int x, int y)
//{
//	int i;
//	int j;
//
//	x *= TILE_SIZE;
//	y *= TILE_SIZE;
//	i = 0;
//	while (i < TILE_SIZE)
//	{
//		j = 0;
//		while (j < TILE_SIZE)
//		{
//			game->img.data[(y  + i) * WIDTH + x + j] = 0xFFFFFF;
//			j++;
//		}
//		i++;
//	}
//}
//
//void	draw_rectangles(t_game *game)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	while (i < ROWS)
//	{
//		j = 0;
//		while (j < COLS)
//		{
//			if (game->map[i][j] == 1) //1인 부분이 올경우
//				draw_rectangle(game, j, i);
//			j++;
//		}
//		i++;
//	}
//}
//
//int		deal_key(int key_code, t_game *game)
//{
//	if (key_code == KEY_ESC)
//		exit(0);
//	return (0);
//}
//
//int 	close(t_game *game)
//{
//	exit(0);
//}
//
//void	game_init(t_game *game)
//{
//	int map[ROWS][COLS] = {
//			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//			{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//			{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
//			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
//			{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
//			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//			{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
//			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//	};
//	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
//}
//
//void	window_init(t_game *game)
//{
//	game->mlx = mlx_init();
//	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
//}
//
//void	img_init(t_game *game)
//{
//	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
//	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
//}
//
//int		main_loop(t_game *game)
//{
//	draw_rectangles(game); // 네모 칸을 그리기.
//	draw_lines(game); // 가로 세로 라인, 선
//	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0); // 이미지에 넣음.
//	return (0);
//}
//
//int		main(void)
//{
//	t_game game;
//
//	game_init(&game); // 지도를 복사해서 game 구조체에 넣음,
//	window_init(&game); // mlx 윈도우 초기화.
//	img_init(&game); // 그릴 이미지 초기화
//	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game); //esc버튼 누를시 종료
//	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close, &game);
//
//	mlx_loop_hook(game.mlx, &main_loop, &game); //main loop함수를 같이 넘겨줌.
//	mlx_loop(game.mlx);
//}
