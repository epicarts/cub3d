#include "../cub3d.h"


void read_map(t_info *info, char *map_path)
{
	int fd;
	char *line;

	check_list_init(info);
	init_dir_duplicate(info);
	if ((fd = open(map_path, O_RDONLY)) == -1)	//파일 디스크립터 얻기
		exit_all(info, "파일 열기 실패", ERROR);
	if (init_identifier(info, fd))
	{
		close(fd); // 파일 읽기 종료
		exit_all(info, "identifier 읽기 실패", ERROR);
	}
	if (!(line = move_map_line(fd)) || read_map_line(info, fd, line)
		|| check_dir_duplicate(info) || info->map_height < 3 || info->map_width < 3)
	{
		close(fd);
		exit_all(info, "맵 읽기 실패", ERROR);
	}
	close(fd);
	fd = open(map_path, O_RDONLY); 	//다시한번 더 파일 읽기. 맵나올떄 부터 ~ 맵 끝까지
	//실패시 프로그램 종료
	if (init_map(info, fd))
		exit_all(info, "맵 검증 실패", ERROR);

	//todo 삭제. 불필요한 코드
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
