
#include "../cub3d.h"


void draw_sprite(t_info *info)
{
	//SPRITE CASTING
	//sort sprites from far to close
	//translate sprite position to relative to camera
	double spriteX = 2.5 - info->pos.x;
	double spriteY = 2.5 - info->pos.y;

	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]

	t_sprite sprite;

	sprite.invDet = 1.0 / (info->plane.x * info->dir.y - info->dir.x * info->plane.y);
	//실제 화면 내부의 깊이.
	set_xy(&sprite.transform, sprite.invDet * (info->dir.y * spriteX - info->dir.x * spriteY),
		   sprite.invDet * (-info->plane.y * spriteX + info->plane.x * spriteY));


	sprite.screen_x = (int)((WIN_WIDTH / 2) * (1 + sprite.transform.x / sprite.transform.y));

	sprite.vMoveScreen = (int)(vMove / sprite.transform.y);

	//calculate height of the sprite on screen
	int spriteHeight = (int)fabs((WIN_HEIGHT / sprite.transform.y) / vDiv); //using "transformY" instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + sprite.vMoveScreen;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + sprite.vMoveScreen;
	if(drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;

	//calculate width of the sprite
	int spriteWidth = (int)fabs((WIN_HEIGHT / sprite.transform.y) / uDiv);
	int drawStartX = -spriteWidth / 2 + sprite.screen_x;
	if(drawStartX < 0) drawStartX = 0;
	int drawEndX = spriteWidth / 2 + sprite.screen_x;
	if(drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;

	//loop through every vertical stripe of the sprite on screen
	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int texX = (int)((256 * (stripe - (-spriteWidth / 2 + sprite.screen_x)) * TEX_WIDTH / spriteWidth) / 256);
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(sprite.transform.y > 0 && stripe > 0 && stripe < WIN_WIDTH && sprite.transform.y < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-sprite.vMoveScreen) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
				int color = info->texture[S].texture[TEX_WIDTH * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) // 검은색이 아닐경우.
					info->buf[y][stripe] = color; // 픽셀 색깔로 칠함.
			}
	}
}