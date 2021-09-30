#include "../includes/so_long.h"

void maperror_output(char **map, char *output)
{
    map = ft_arrayfree(map);
    ft_putstr_fd("Error(Map): ", 2);
	ft_putstr_fd(output, 2);
	exit(EXIT_SUCCESS);
}