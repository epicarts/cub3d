
#include "../cub3d.h"

void draw_wall(t_info *info, t_ray *ray, int x)
{
	// win 높이를 사용해서 벽의 높이를 구함
	int lineHeight = (int)(WIN_HEIGHT / ray->perp_wall_dist); //거리에 반비례.

	//텍스쳐의 시작 위치로 활용가능.
	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if(drawStart < 0) // 시작 위치가 음수일경우 0부터 그리도록.
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2; // 끝나는 높이 좌표.
	if(drawEnd >= WIN_HEIGHT) // 높이가 초과될경우 화면의 가장 끝에 보이도록.
		drawEnd = WIN_HEIGHT - 1;

	// 벽과 double  거리
	double wallX;
	if (ray->side == 0)
		wallX = info->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wallX = info->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	wallX -= floor(wallX);

	// x coordinate on the texture
	// 벽과 거리와 텍스쳐 두께를 이용해 texX를 구함.
	int texX = (int)(wallX * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		texX = TEX_WIDTH - texX - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		texX = TEX_WIDTH - texX - 1;

	// How much to increase the texture coordinate perscreen pixel
	double step_ = 1.0 * TEX_HEIGHT / lineHeight; // 2.0으로 할경우 벽이 가로 두개로 나뉘어짐.

	int color;
	//텍스쳐의 위치.
	double texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step_;
	for (int y = drawStart; y <= drawEnd; y++) // y좌표를 그린다.
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step_;
		// 위치에 맞는 데이터를 가져옴.
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (ray->side == 1) // y벽면에 부딪히는경우.
		{
			if (ray->ray_dir.y < 0)
				color = info->texture[WE].texture[TEX_HEIGHT * texY + texX]; // 서쪽
			else
				color = info->texture[EA].texture[TEX_HEIGHT * texY + texX]; // 동쪽
		}
		else //x 벽면에 부딪히는 경우.
		{
			if (ray->ray_dir.x < 0) //x의 진행방향이 음수.
				color = info->texture[NO].texture[TEX_HEIGHT * texY + texX]; // 북쪽
			else // x의 진행방향이 양수
				color = info->texture[SO].texture[TEX_HEIGHT * texY + texX]; // 남쪽
		}
		info->buf[y][x] = color;
	}

	//SET THE ZBUFFER FOR THE SPRITE CASTING
	// 각 레이캐스팅의 수선의 발 정보들을 저장해놓는다.
	info->zBuffer[x] = ray->perp_wall_dist; //perpendicular distance is used
}