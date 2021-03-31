
#include "../cub3d.h"

void check_list_init(t_info *info);

void read_map(t_info *info, char *map_path)
{
	//맵초기화.
	int fd;
	int i;
	char *line;

	info->win_y = 0;
	check_list_init(info);

	//파일 디스크립터 얻기
	if (!(fd = open(map_path, O_RDONLY))) {
		printf("\nError in open\n"); // todo exit program
		exit(0);
	}

	//한줄씩 읽음.
	//맨 처음에 데이터

	//정보 초기화.
	// 실패시 프로그램 종료
	if (init_identifier(info, fd))
	{
		printf("identifier 읽기 실패");
		close(fd); // 파일 읽기 종료
		exit(0);
	}


	// 맵 읽기
	//실패시 프로그램 종료
	if (init_map(info, fd))
	{
		printf("맵 읽기 실패");
		exit(0);
	}

	//printf("맵 검증 실패");

	printf("파일 읽기 종료");
	close(fd);

	//지도를 다 불러놓음.
//	map_validation(); //맵에 대한 검증.
}

void check_list_init(t_info *info) {
	info->read_check.r = 0;
	info->read_check.no = 0;
	info->read_check.so = 0;
	info->read_check.we = 0;
	info->read_check.ea = 0;
	info->read_check.s = 0;
	info->read_check.f = 0;
	info->read_check.c = 0;
}
