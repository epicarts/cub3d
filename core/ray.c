

#include "../cub3d.h"

void calc_ray_step(t_info *info, t_ray *ray)
{
	if (ray->ray_dir.x < 0) // 왼쪽 방향으로 쐇다.
	{
		ray->step.x = -1; //x가 음의 방향인가?
		ray->side_dist.x = (info->pos.x - ray->map.x) * ray->delta_dist.x; //플레이어 - 맵.
	}
	else
	{
		ray->step.x = 1; //x가 양의 방향인가?
		ray->side_dist.x = (ray->map.x + 1.0 - info->pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (info->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - info->pos.y) * ray->delta_dist.y;
	}
}

void DDA_algorithm(t_info *info, t_ray *ray)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		// y가 더 가파른 경우. y의 증가폭이 큰경우. x를 1씩 증가시켜야함.
		if(ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x; //다음번 x선을 만날떄까지 길이를 계속 더해줌.
			ray->map.x += (int)ray->step.x; //오른쪽으로 x가 움직이는지 왼쪽으로 움직이는지. 기울기가 음수 양수
			ray->side = 0; //세로선과 부딪힘.  //위아래선이냐, 오른쪽 왼쪽 선이냐
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y; //다음번 y선을 만날떄까지 길이를 계속 더해줌
			ray->map.y += (int)ray->step.y;//ray 오른쪽으로 왼쪽으로 움직이는지. 기울기가 음수 양수
			ray->side = 1; // 가로선과 부딪힘.
		}
		if (info->world_map[(int)ray->map.x][(int)ray->map.y] == 1) // 벽은 1로 표현되어짐. todo
			hit = 1;
	}
}

void	calc_ray(t_info *info, t_ray *ray, int x)
{
	double K; // -1 ~ 1 로 정규화. 0 일떄 -1 / x가 최대값이면 2 - 1 = 1

	K = 2 * x / (double)info->win_x - 1; //ray의 방향. plane의 k배수
	set_xy(&ray->ray_dir,info->dir.x + info->plane.x * K, info->dir.y + info->plane.y * K);//내림을 통해 내 현재 광선 위치.
	set_xy(&ray->map, (int)info->pos.x, (int)info->pos.y);
	set_xy(&ray->delta_dist, fabs(1. / ray->ray_dir.x), fabs(1. / ray->ray_dir.y));
	calc_ray_step(info, ray);
	DDA_algorithm(info, ray); //DDA 알고리즘 칸수 체크하면서 hit되었는지 봄.
	//레이에서 hit되었을때 카메라 평면과의 수선의 발의 길이. 둥글게 보임.
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - info->pos.x + (1 - ray->step.x) / 2) / ray->ray_dir.x; //step은 1
	else
		ray->perp_wall_dist = (ray->map.y - info->pos.y + (1 - ray->step.y) / 2) / ray->ray_dir.y;
}
