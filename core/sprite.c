
#include "../cub3d.h"

void init_sprite(t_info *info, t_sprite_calc *sc, t_xy *sprite)
{
	sprite->x = (sprite->x + 0.5) - info->pos.x;
	sprite->y = (sprite->y + 0.5) - info->pos.y;
	sc->invDet = 1.0 / (info->plane.x * info->dir.y - info->dir.x * info->plane.y); //역행렬
	set_xy(&sc->transform, sc->invDet * (info->dir.y * sprite->x - info->dir.x * sprite->y), //실제 화면 내부의 깊이.
		   sc->invDet * (-info->plane.y * sprite->x + info->plane.x * sprite->y));
	sc->screen_x = (int)((WIN_WIDTH / 2) * (1 + sc->transform.x / sc->transform.y));
	sc->spriteHeight = (int)fabs((WIN_HEIGHT / sc->transform.y) / vDiv); //using "transformY" instead of the real distance prevents fisheye
	sc->vMoveScreen = (int)(vMove / sc->transform.y);
	sc->drawStartY = -sc->spriteHeight / 2 + WIN_HEIGHT / 2 + sc->vMoveScreen; 	//스프라이트 시작지점과 끝나는 곳. 화면의 y좌표
	if(sc->drawStartY < 0)
		sc->drawStartY = 0;
	sc->drawEndY = sc->spriteHeight / 2 + WIN_HEIGHT / 2 + sc->vMoveScreen;
	if(sc->drawEndY >= WIN_HEIGHT)
		sc->drawEndY = WIN_HEIGHT - 1;
	sc->spriteWidth = (int)fabs((WIN_HEIGHT / sc->transform.y) / uDiv);
	sc->drawStartX = -sc->spriteWidth / 2 + sc->screen_x;
	if (sc->drawStartX < 0)
		sc->drawStartX = 0;
	sc->drawEndX = sc->spriteWidth / 2 + sc->screen_x;
	if(sc->drawEndX >= WIN_WIDTH)
		sc->drawEndX = WIN_WIDTH - 1;
}

void draw_sprite(t_info *info, t_xy sprite)
{
	t_sprite_calc sc;
	int y;
	int x;

	init_sprite(info, &sc, &sprite);
	x = sc.drawStartX - 1;
	while (++x <= sc.drawEndX)
	{
		sc.texX = (int)((256 * (x - (-sc.spriteWidth / 2 + sc.screen_x)) * TEX_WIDTH / sc.spriteWidth) / 256);
		// sprite.transform.y > 0 음수면 반대쪽 카메라에 보임.
		// && stripe > 0 && stripe < WIN_WIDTH  화면에 있습니다. 왼쪽 오른쪽인듯 ? on the screen
		// sprite.transform.y < info->zBuffer[stripe] => 벽 뒤에 있는지 앞에 있는지 판별. 이전에 저장해놓은 벽과 카메라 수선의 발사이즈.
		if (sc.transform.y > 0 && x >= 0 && x < WIN_WIDTH && sc.transform.y < info->zBuffer[x])
			y = sc.drawStartY - 1;
		while (++y <= sc.drawEndY)
		{
			sc.d = (y - sc.vMoveScreen) * 256 - WIN_HEIGHT * 128 + sc.spriteHeight * 128;//256 and 128 factors to avoid floats ??? 먼지 모르겟음.
			sc.texY = ((sc.d * TEX_HEIGHT) / sc.spriteHeight) / 256;
			if (0 <= TEX_WIDTH * sc.texY + sc.texX) // 버그 방지.
			{
				sc.color = info->texture[S].texture[TEX_WIDTH * sc.texY + sc.texX]; //텍스쳐에서 값들을 가져옴.
				if((sc.color & 0x00FFFFFF) != 0) // 검은색이 아닐경우.
					info->buf[y][x] = sc.color; // 픽셀 색깔로 칠함.
			}
		}
	}
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int i;
	int j;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void sort_sprites(int* order, double* dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = -1;
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	while (++i < amount) //sprites에 모든 값들을 다 저장.
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount); //std::sort(sprites.begin(), sprites.end());
	i = -1;
	while (++i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void draw_sprites(t_info *info)
{
	int i;

	i = -1;
	while (++i < info->sprite_count)
	{
		info->sprite_order[i] = i; //현재 인덱스를 기록.
		info->sprite_distance[i] = ((info->pos.x - info->sprite[i].x) * (info->pos.x - info->sprite[i].x) +
				(info->pos.y - info->sprite[i].y) * (info->pos.y - info->sprite[i].y)); //sqrt not taken, unneeded
	}
	sort_sprites(info->sprite_order, info->sprite_distance, info->sprite_count);

	i = -1;
	while (++i < info->sprite_count)
		draw_sprite(info, info->sprite[info->sprite_order[i]]);
}