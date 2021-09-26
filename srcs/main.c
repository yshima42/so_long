#include "../includes/so_long.h"


int	extension_check(char *filename)
{
	char *dot_ptr;
	
	dot_ptr = ft_strchr(filename, '.');
	if(dot_ptr == NULL)
		return (-1);
	else
	{
		if(ft_strncmp(dot_ptr, ".bar", 4))
			return (-1);
	}
	return (0);
}

void	args_check(int ac, char **av)
{
	if(ac != 2)
	{
		printf("You need two args: ./so_long xxx.bar");
		exit (0);
	}
	if(extension_check(av[1]) == -1)
	{
		printf("You need to have xxx.bar file");
		exit (0);
	}
}



int main(void)//int ac, char **av)
{
	//t_conf	conf;
	/* t_vars	vars; */
	void *mlx;
	void *win;
	
	//args_check(ac, av);
	/* vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx); */
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}