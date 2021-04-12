#include "../cub3d.h"

void arg_parse(t_info *info, int argc, char *argv[])
{
	// 인자가 두개 이상왔는데, save가 옵션이 아닐경우. 종료
	if (argc >= 3 && ft_strcmp(argv[2] , "--save")) //2번쨰 인자가 올경우
		exit_all(info, "올바른 인자가 아님", ERROR);
	else if (argc == 2)
		info->screenshot_flag = 0;
	else
		info->screenshot_flag = 1;
	if (argc == 1) // 인자가 아무것도 없으면 종료.
		exit_all(info, "인자가 아무것도 없음. 맵을 넣어주세요.", ERROR);
	info->map_path = argv[1];
}
