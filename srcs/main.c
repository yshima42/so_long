#include "../includes/so_long.h"

typedef	struct s_player
{
	int	pos_y;
	int	pos_x;
	size_t	n_steps;
	size_t	n_collectibles;
} t_player;

typedef	struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	uint8_t	map_flag;
}	t_map;

typedef struct s_images
{
	void	*empty;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
	int		size;
}	t_images;

typedef struct s_conf
{
    void		*mlx;
	void		*win;
	t_map		map;
	t_images	images;
	t_player	player;
}	t_conf;

# define FLAG_EMPTY 		1 << 0 // 0000 0001
# define FLAG_WALL 			1 << 1 // 0000 0010
# define FLAG_COLLECTIBLE 	1 << 2 // 0000 0100
# define FLAG_EXIT 			1 << 3 // 0000 1000
# define FLAG_PLAYER 		1 << 4 // 0001 0000

# define VALID_CHAR 		"01CEP"

# define IMG_EMPTY 			"images/empty.xpm"
# define IMG_WALL 			"images/wall.xpm"
# define IMG_COLLECTIBLE	"images/bitcoin2.xpm"
# define IMG_EXIT 			"images/exit.xpm"
# define IMG_PLAYER 		"images/player.xpm"

# define CHIP_SIZE 			32

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100


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
char	**lst_to_array(t_list *buf, size_t height, char **map)
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

void sl_line_check(char *line, size_t height, t_conf *conf)
{
	size_t	i;

	if (height == 0)
		conf->map.width = ft_strlen(line);
	if (conf->map.width != ft_strlen(line))
	{
		printf("not rec error");
		exit(EXIT_SUCCESS);
	}
	i = -1;
	while (line[++i])
	{
		if(ft_strchr(VALID_CHAR, line[i]) == NULL)
		{
			ft_putstr_fd("bad char", 2);
			exit(EXIT_SUCCESS);
		}
	}
}

size_t	file_to_lst(int fd, t_list **buf, t_conf *conf)
{
	char	*line;
	size_t	l_count;
	
	l_count = 0;
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (l_count == 0)
			*buf = ft_lstnew(line);
		else
			ft_lstadd_back(buf, ft_lstnew(line));
		sl_line_check(line, l_count, conf);
		l_count++;
	}
	return (l_count);
}

char	**map_set(char *mapfile, t_conf *conf)
{
	int	fd;
	t_list	*buf;

	buf = NULL;
	fd = ft_open_readfile(mapfile);
	conf->map.height = file_to_lst(fd, &buf, conf);
	return (lst_to_array(buf, conf->map.height, conf->map.map));
}


void	*chr_to_imgptr(char c, t_conf *conf)
{
	if (c == '0')
		return (conf->images.empty);
	else if (c == '1')
		return (conf->images.wall);
	else if (c == 'C')
		return (conf->images.collectible);
	else if (c == 'E')
		return (conf->images.exit);
	else if (c == 'P')
		return (conf->images.player);
	else
	{
		ft_putstr_fd("never come here", 2);
		exit(0); // it shouldn't come here
	}
}

void	player_pos_set(int i, int j, t_conf *conf)
{
	conf->player.pos_y = i;
	conf->player.pos_x = j;
}

void	array_to_screan(char **map, t_conf *conf)
{
	void	*img_ptr;
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j]) // error handring player only be one
		{
			img_ptr = chr_to_imgptr(map[i][j], conf);
			mlx_put_image_to_window(conf->mlx, conf->win, img_ptr, CHIP_SIZE * j, CHIP_SIZE * i);
		}
	}
}

void	chip_set(t_conf *conf)
{
	conf->images.size = 32;
	conf->images.empty = mlx_xpm_file_to_image(conf->mlx, IMG_EMPTY, &conf->images.size, &conf->images.size);
	conf->images.wall = mlx_xpm_file_to_image(conf->mlx, IMG_WALL, &conf->images.size, &conf->images.size);
	conf->images.collectible = mlx_xpm_file_to_image(conf->mlx, IMG_COLLECTIBLE, &conf->images.size, &conf->images.size);
	conf->images.exit = mlx_xpm_file_to_image(conf->mlx, IMG_EXIT, &conf->images.size, &conf->images.size);
	conf->images.player = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER, &conf->images.size, &conf->images.size);
}

int	close_window(t_conf *conf)
{
	//free_map(conf);
	//img_ptr_destroy(conf); // need to free many things
	mlx_destroy_window(conf->mlx, conf->win);
	mlx_destroy_display(conf->mlx);
	free(conf->mlx);
	exit(0);
	return (0);
}

void ft_swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void player_pos_check(char **map, t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j]) // error handring player only be one
		{
			if (map[i][j] == 'P')
				player_pos_set(i, j, conf);
		}
	}
}

void step_counter(t_conf *conf)
{
	conf->player.n_steps++;
	printf("Number of steps: %ld\n", conf->player.n_steps);
}

int	movable_check(char c)
{
	if (c == '1')
		return (0);
	else
		return (1);
}

int collectible_check(char c)
{
	if (c == 'C')
		return (1);
	else
		return (0);	
}

void	collect_item(char *a, char *b, t_conf *conf)
{
	*b = *a;
	*a = '0';
	conf->player.n_collectibles++;
}

void	next_step(char *current_pos, char *next_pos, t_conf *conf)
{
	if (collectible_check(*next_pos))
		collect_item(current_pos, next_pos, conf);
	else if (movable_check(*next_pos))
		ft_swap(current_pos, next_pos);
}

void player_move(int keycode, t_conf *conf)
{
	int x;
	int y;

	x = conf->player.pos_x;
	y = conf->player.pos_y;
	step_counter(conf);
	if (keycode == W_KEY)
		next_step(&conf->map.map[y][x], &conf->map.map[y - 1][x], conf);
	if (keycode == A_KEY)
		next_step(&conf->map.map[y][x], &conf->map.map[y][x - 1], conf);
	if (keycode == S_KEY)
		next_step(&conf->map.map[y][x], &conf->map.map[y + 1][x], conf);
	if (keycode == D_KEY)
		next_step(&conf->map.map[y][x], &conf->map.map[y][x + 1], conf);
}

int	key_hook(int keycode, t_conf *conf)
{
	void *img;
	int	size = 32;

	player_pos_check(conf->map.map, conf);
	if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY)
		player_move(keycode, conf);
	if (keycode == ESC_KEY)
		close_window(conf);
	array_to_screan(conf->map.map, conf);
	return (0);

	img = mlx_xpm_file_to_image(conf->mlx, "images/player.xpm", &size, &size);
	if (keycode == W_KEY)
	{
		mlx_put_image_to_window(conf->mlx, conf->win, img, 1, 1);
		mlx_destroy_image(conf->mlx, img);
		printf("Hello from key_hook!\n");
	}
	if(keycode == A_KEY)
	{
		mlx_put_image_to_window(conf->mlx, conf->win, img, 32, 32);
		mlx_destroy_image(conf->mlx, img);
		printf("a\n");
	}
	if(keycode == S_KEY)
	{
		mlx_put_image_to_window(conf->mlx, conf->win, img, 64, 64);
		mlx_destroy_image(conf->mlx, img);
		printf("a\n");
	}
    return(0);
}

int main(int ac, char **av)
{
	t_conf	conf;
	
	conf.player.n_steps = 0; // need to initialize some variable
	args_check(ac, av);
	conf.map.map = map_set(av[1], &conf);
	player_pos_check(conf.map.map, &conf);
	conf.mlx = mlx_init();
	chip_set(&conf);
 	conf.win = mlx_new_window(conf.mlx, 800, 500, "so_long");
	mlx_key_hook(conf.win, key_hook, &conf);
	mlx_loop(conf.mlx);
}