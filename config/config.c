#include "../cub3d.h"


void read_map(t_info *info, char *map_path)
{
	//맵초기화.
	int fd;
	char *line;

	info->win_y = 0;
	check_list_init(info);
	init_dir_duplicate(info);
	//파일 디스크립터 얻기
	if (!(fd = open(map_path, O_RDONLY))) {
		perror("Error in open"); // todo exit program
		exit(0);
	}
	if (init_identifier(info, fd))
	{
		perror("identifier 읽기 실패");
		close(fd); // 파일 읽기 종료
		exit(0);
	}
	if (!(line = move_map_line(info, fd)) || read_map_line(info, fd, line)
		|| check_dir_duplicate(info) || info->map_height < 3 || info->map_width < 3)
	{
		perror("맵을 읽어오는 도중 이상한 것을 발견함");
		close(fd);
		exit(0);
	}
	close(fd);
	//다시한번 더 파일 읽기. 맵나올떄 부터 ~ 맵 끝까지
	fd = open(map_path, O_RDONLY);
	//실패시 프로그램 종료
	if (init_map(info, fd))
	{
		printf("맵 읽기 실패");
		exit(0);
	}
	printf("E: %d N:%d S:%d W:%d\n", info->dir_check.e, info->dir_check.n,info->dir_check.s, info->dir_check.w);
	printf("맵사이즈: %d %d\n", info->map_width, info->map_height);
	printf("위치 %f %f\n", info->pos.x, info->pos.y);
	for (int i = 0; i<info->map_height; i++)
	{
		for (int j = 0; j<info->map_width; j++)
			printf("%d ", info->world_map[i][j]);
		printf("\n");
	}
	close(fd);
	//지도를 다 불러놓음.
//	map_validation(); //맵에 대한 검증.
}
