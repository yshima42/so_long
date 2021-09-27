#include "../includes/so_long.h"

typedef	struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_map;


typedef struct s_conf
{
    void	*mlx;
	void	*win;
	t_map	map;
}	t_conf;

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

/* void	chip_set(t_conf	*conf)
{

} */

int	ft_open_readfile(char *readfile)
{
	int fd;

	fd = open(readfile, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}


// think if you need to return char** or int
char	**lst_to_2darray(t_list *buf, size_t height, char **map)
{
	t_list	*t_buf;
	size_t	i;
	
	t_buf = buf;
	map = (char **)malloc(sizeof(char *) * height + 1);
	if (!map)
		exit(EXIT_FAILURE);//need perror??
	i = 0;
	while (t_buf)
	{
		map[i] = ft_strdup(t_buf->content);
		t_buf = t_buf->next;
		i++;
	}
	map[i] = NULL;
	ft_lstclear(&buf, free);
	return (map);
}

void	map_check_set(char *mapfile, t_conf *conf)
{
	int	fd;
	t_list	*buf;
	char	*line;
	size_t	height;

	height = 1;
	fd = ft_open_readfile(mapfile);
	buf = ft_lstnew(get_next_line(fd));
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		//line_check(line, height, conf);
		ft_lstadd_back(&buf, ft_lstnew(line));
		height++;
	}
	conf->map.height = height;
	conf->map.map = lst_to_2darray(buf, conf->map.height, conf->map.map);
	
}

int main(int ac, char **av)
{
	t_conf	conf;
	
	args_check(ac, av);
	map_check_set(av[1], &conf);
	conf.mlx = mlx_init();
	/* chip_set(&conf); */
 	conf.win = mlx_new_window(conf.mlx, 800, 500, "so_long");
	
	mlx_loop(conf.mlx);
}