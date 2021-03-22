//
// Created by YoungHo on 2021/03/20.
//

#include "cub3d.h"

void map_init();

void map_validation();

typedef struct s_param{
	int		x;
	int		y;
	char	str[3];
}				t_param;

//Only param->x will be used.
void			param_init(t_param *param)
{
	param->x = 3;
	param->y = 4;
	param->str[0] = 'a';
	param->str[1] = 'b';
	param->str[2] = '\0';
}

//keycode는 내가 누른 키보드 입력값.
int				key_press(int keycode, t_param *param)
{
	static int a = 0;

	// W 버튼일때 x증가.
	if (keycode == KEY_W)//Action when W key pressed
		param->x++;
	else if (keycode == KEY_S) //s키 일때,
		param->x--;
	else if (keycode == KEY_ESC) //프로그램 종료.
		exit(0);
	printf("x: %d\n", param->x);
	return (0);
}

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
}				t_mlx;


typedef struct	s_img
{
	void		*img_ptr;
	int			*data;

	// 커스텀. 폭, 높이
	int			width;
	int			height;
	//You don't need to understand the 3 values below.
	//After declaration, it will be automatically initialized when passed to mlx_get_data_addr function.
	//아래 3개 값은 이해 안해도 사용하는데 지장이 없음.
	//선언한뒤 함수의 인자로만 잘 넣어주면 알아서 정보를 받아나옴.
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;



# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

#define mapWidth 24
#define mapHeight 24

// 2차원 배열의 맵.
int worldMap[mapWidth][mapHeight]=
{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int			main(void)
{
	t_mlx	*mlx;
	int		count_w;
	int		count_h;
	t_img	img;

	t_param		param;

	map_init(); //맵 초기화



	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");



	//img 구조체에 적절한 값을 넣음.
	//새로운 이미지. mlx포인터, 이미지 폭, 높이. 반환값으로 이미지 포인터 주소.
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	//img 1차원 포인터에 int 형변환하여 포인터 주소를 넣음.
	//이미지 포인터, bpp, size, endian 을 순서대로... img.data에 포인터가 담김.
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

	//img.data 에 값들을 넣음.
	count_h = -1;
	while (++count_h < IMG_HEIGHT) // 0, 1, 2, 3, 4, 5....500
	{
		count_w = -1;
		while (++count_w < IMG_WIDTH) // 0, 1, 2, 3, 4. ..600
		{
			printf("%d\n", count_h * IMG_WIDTH + count_w);// 0 * 600 + 1 = 1, 2, 3, 4, 5 ... 601,602,603... 119999
			if (count_w % 2) // 2칸 마다 하나씩.
				img.data[count_h * IMG_WIDTH + count_w] = 0xFF00FF;
			else
				img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF;
		}
	}
	img.data[count_h * IMG_WIDTH + count_w] = 0x000000;
	//이미지를 윈도우에 넣음.
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 100, 100);


	//free()를 해줘야할듯;
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	count_h = -1;
	while (++count_h < IMG_HEIGHT) // 0, 1, 2, 3, 4, 5....500
	{
		count_w = -1;
		while (++count_w < IMG_WIDTH) // 0, 1, 2, 3, 4. ..600
		{
			printf("%d\n", count_h * IMG_WIDTH + count_w);// 0 * 600 + 1 = 1,
			if (count_w % 2) // 2칸 마다 하나씩.
				img.data[count_h * IMG_WIDTH + count_w] = 0x777777;
			else
				img.data[count_h * IMG_WIDTH + count_w] = 0x000000;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 300, 300);

//	img.width = 100;
//	img.height = 100;
	img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "../textures/wall_n.xpm", &img.width, &img.height);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	count_h = -1;
	while (++count_h < img.height)
	{
		count_w = -1;
		while (++count_w < img.width / 2)
		{
			if (count_w % 2)
				img.data[count_h * img.width + count_w] = 0xFFFFFF;
			else
				img.data[count_h * img.width + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 150, 150);



	// keyboard
	param_init(&param);

	//키 이벤트, 키 함수.
	mlx_hook(mlx->win, X_EVENT_KEY_PRESS, 0, &key_press, &param);


	// mlx 포인터, win ,
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

void map_init() {
	//맵초기화.

	map_validation(); //맵에 대한 검증.
}

void map_validation() {
	//맵에 대한 검증.

}





