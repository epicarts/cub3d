#include "../cub3d.h"

// int 로 1024 라고 한다면 0000 1000 0000 0000(2) 이렇게 됨.
void int_to_char(unsigned char *str, int value)
{
	str[0] = (unsigned char)(value); // 0000
	str[1] = (unsigned char)(value >> 8); //0000
	str[2] = (unsigned char)(value >> 16); //1000 = 08(10)
	str[3] = (unsigned char)(value >> 24); //0000
}

int		write_bmp_header(int fd, int file_size) {
	unsigned char bmp_header[54];

	ft_bzero(bmp_header, 54);
	bmp_header[0] = (unsigned char) ('B');
	bmp_header[1] = (unsigned char) ('M');
	// 헤더 사이즈 + 이미지 사이즈 = filesize
	int_to_char(bmp_header + 2, file_size); // 헤더의 두번쨰 에 파일 사이즈를 입력.
	bmp_header[10] = (unsigned char) (54);
	bmp_header[14] = (unsigned char) (40);
	int_to_char(bmp_header + 18, WIN_WIDTH);
	int_to_char(bmp_header + 22, WIN_HEIGHT);
	bmp_header[26] = (unsigned char) (1);
	bmp_header[28] = (unsigned char) (32);
	if (write(fd, bmp_header, 54) < 0)
		return (0);
	return (1);
}

int write_bmp_data(int fd, t_info *info)
{
	int y;
	int x;

	y = WIN_HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// 0x00123456 =>이렇게 저장되어 있으면, 65 34 12 00으로 어케 저장하
			if (write(fd, &(info->buf[y][x]), 4) < 0) //24bit 비트맵. 00 ff ff ff
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int save_bmp(t_info *info)
{
	int file_size;
	int fd;

	// O_TRUNC 자르기. O_WRONLY 쓰기전용 / O_CREAT 없으면 만들기
	if (!(fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666)))
		return (0);

	file_size = 54 + (4 * WIN_WIDTH  * WIN_HEIGHT); // 헤더사이즈 4 추가.
	if (!write_bmp_header(fd, file_size))
		return (0);
	if (!write_bmp_data(fd, info))
		return (0);
	close(fd);
	return (1);
}


void screenshot(t_info *info)
{
	if (!save_bmp(info))
	{
		printf("세이브 실패");
		exit(1);
	}
	printf("세이브 성공");
	exit(1);
	//todo 메모리 초기화 하면서 종료하도록 해야함. exit 함수 만들고 작업 예정.
}

