#include "../includes/so_long.h"

int main()
{
	int fd1;
	//int fd2;

	fd1 = open("./srcs/file", O_RDONLY);
	//fd2 = open("test/sample2", O_RDONLY);
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
	//printf("%s", get_next_line(fd2));
	printf("%s",get_next_line(fd1));
	//printf("%s",get_next_line(fd2));

	close(fd1);
	//close(fd2);	

	printf("%zu",ft_strlen("aaaaaa"));
	return 0;
}