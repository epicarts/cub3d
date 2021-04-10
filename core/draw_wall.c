
#include "../cub3d.h"

void init_wall(t_info *info, t_wall_calc *w, t_ray *ray)
{
	w->lineHeight = (int)(info->win_y / ray->perp_wall_dist); //거리에 반비례. 벽의 높이를 구함.
	w->drawStart = -w->lineHeight / 2 + info->win_y / 2; //텍스쳐의 시작 위치로 활용가능.
	if(w->drawStart < 0) // 시작 위치가 음수일경우 0부터 그리도록.
		w->drawStart = 0;
	w->drawEnd = w->lineHeight / 2 + info->win_y / 2; // 끝나는 높이 좌표.
	if(w->drawEnd >= info->win_y) // 높이가 초과될경우 화면의 가장 끝에 보이도록.
		w->drawEnd = info->win_y - 1; // 599가 됨.
	if (ray->side == 0)
		w->wallX = info->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		w->wallX = info->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	w->wallX -= floor(w->wallX);
	w->texX = (int)(w->wallX * (double)TEX_WIDTH);	// 벽과 거리와 텍스쳐 두께를 이용해 texX를 구함.
	if (ray->side == 0 && ray->ray_dir.x > 0)
		w->texX = TEX_WIDTH - w->texX - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		w->texX = TEX_WIDTH - w->texX - 1;
	w->step_ = 1.0 * TEX_HEIGHT / w->lineHeight; // 2.0으로 할경우 벽이 가로 두개로 나뉘어짐.
	w->texPos = (w->drawStart - info->win_y / 2 + w->lineHeight / 2) * w->step_;
}


void draw_wall(t_info *info, t_ray *ray, int x)
{
	t_wall_calc	w;
	int y;

	init_wall(info, &w, ray);
	y = w.drawStart;
	while (y <= w.drawEnd)// y좌표를 그린다. 0 ~ drawEnd(599)
	{
		w.texY = (int)w.texPos & (TEX_HEIGHT - 1);
		w.texPos += w.step_;	// 위치에 맞는 데이터를 가져옴.
		if (ray->side == 1) // y벽면에 부딪히는경우.
		{
			if (ray->ray_dir.y < 0)
				w.color = info->texture[WE].texture[TEX_HEIGHT * w.texY + w.texX]; // 서쪽
			else
				w.color = info->texture[EA].texture[TEX_HEIGHT * w.texY + w.texX]; // 동쪽
		}
		else //x 벽면에 부딪히는 경우.
		{
			if (ray->ray_dir.x < 0) //x의 진행방향이 음수.
				w.color = info->texture[NO].texture[TEX_HEIGHT * w.texY + w.texX]; // 북쪽
			else // x의 진행방향이 양수
				w.color = info->texture[SO].texture[TEX_HEIGHT * w.texY + w.texX]; // 남쪽
		}
		info->buf[y][x] = w.color;
		y++;
	}
	draw_ceiling(info, x, w);
	draw_floor(info, x, w);
	info->zBuffer[x] = ray->perp_wall_dist; 	// 각 레이캐스팅의 수선의 발 정보들을 저장해놓는다.
}
