#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>

#define mapWidth 24
#define mapHeight 24

void	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i]);
	write(1, str, i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	int neg;

	neg = 0;
	neg = nb < 0 ? 1 : 0;
	neg ? ft_putchar('-') : 0;
	if (nb == -2147483648)
		ft_putstr("2147483648");
	if (nb == 0)
		ft_putchar('0');
	if (nb == 0 || nb == -2147483648)
		return ;
	nb < 0 ? (nb = -nb) : 0;
	if (nb == 0)
		ft_putchar(0);
	nb > 9 ? ft_putnbr(nb / 10) : 0;
	ft_putchar(nb % 10 + '0');
}

typedef struct    data_s
{
    void	*mlx_ptr;
    void	*mlx_win;
    int		s_w;
    int		s_h;
    
}                 data_t;

typedef struct var_s
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;
	int		ESC;
	int		W;
	int		A;
	int		S;
	int		D;
	void	*img;
	int	endian;
	int	bpp;
	int	line;
	int	offset;
	int	x;
	int	s_h;
	int	s_w;
	char	*addr;
}	var_t;

void	pixel_put(var_t *var, int x, int y, int color)
{
	char *dst;

	dst = var->addr + (y * var->line + x * (var->bpp / 8));
	*(unsigned int*)dst = color;
}

int	verline(var_t *var, int x, int draw_start, int draw_end, int color)
{
	int swap;

	if (draw_end < draw_start)
	{
		swap = draw_start;
		draw_start = draw_end;
		draw_end = swap;
	}
	if (draw_end < 0 || draw_start >= var->s_h || x < 0 || x >= var->s_w)
		return (0);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= var->s_w)
		draw_end = var->s_h - 1;
	while (draw_start < draw_end)
	{
		pixel_put(var, x, draw_start, color);
		draw_start++;
	}
	return (1);
}

void	init_raycast(data_t *data, var_t *var)
{
	var->s_w = data->s_w;
	var->s_h = data->s_h;
	var->img = mlx_new_image(data->mlx_ptr, data->s_w, data->s_h);
	var->addr = mlx_get_data_addr(var->img, &var->bpp, &var->line, &var->endian);
	var->posX = 22;
	var->posY = 12;
	var->dirX = -1;
	var->dirY = 0;
	var->planeX = 0;
	var->planeY = 0.66;
	var->time = 0;

}

void	step(var_t *var)
{
	if (var->rayDirX < 0)
	{
		var->stepX = -1;
		var->sideDistX = (var->posX - var->mapX) * var->deltaDistX;
	}
	else
	{
		var->stepX = 1;
		var->sideDistX = (var->mapX + 1.0 - var->posX) * var->deltaDistX;
	}
	if (var->rayDirY < 0)
	{
		var->stepY = -1;
		var->sideDistY = (var->posY - var->mapY) * var->deltaDistY;
	}
	else
	{
		var->stepY = 1;
		var->sideDistY = (var->mapY + 1.0 - var->posY) * var->deltaDistY;
	}
}

void	hit(int worldMap[mapWidth][mapHeight], var_t *var)
{
	while (var->hit == 0)
	{
		if (var->sideDistX < var->sideDistY)
		{
			var->sideDistX += var->deltaDistX;
			var->mapX += var->stepX;
			var->side = 0;
		}
		else
		{
			var->sideDistY += var->deltaDistY;
			var->mapY += var->stepY;
			var->side = 1;
		}
		if (worldMap[var->mapX][var->mapY] > 0)
			var->hit = 1;
	}
	if (var->side == 0)
		var->perpWallDist = (var->mapX - var->posX + (1 - 
		var->stepX) / 2) / var->rayDirX;
	else
		var->perpWallDist = (var->mapY - var->posY + (1 - var->stepY) / 2) / var->rayDirY;	
}

void	draw(var_t *var, data_t *data, var_info_t *var)
{
	var->lineHeight = (int)(data->s_h / var->perpWallDist);
	var->drawStart = -var->lineHeight / 2 + data->s_h / 2;
	if (var->drawStart < 0)
		var->drawStart = 0;
	var->drawEnd = var->lineHeight / 2 + data->s_h / 2;
	if (var->drawEnd >= data->s_h)
		var->drawEnd = data->s_h - 1;
	var->color = 255;
	if (var->side == 1)
		var->color = var->color / 2;
	verline(var, var->x, var->drawStart, var->drawEnd, var->color);
}

void	raycast(var_info_t *var, data_t *data, var_t *var,
int worldMap[mapWidth][mapHeight])
{
	var->x = 0;
	while (var->x < data->s_w)
	{
		var->cameraX = 2 * var->x / (double)data->s_w - 1;
		var->rayDirX = var->dirX + var->planeX * var->cameraX;
		var->rayDirY = var->dirY + var->planeY * var->cameraX;
		var->mapX = (int)var->posX;
		var->mapY = (int)var->posY;
		var->deltaDistX = fabs(1 / var->rayDirX);
		var->deltaDistY = fabs(1 / var->rayDirY);
		var->hit = 0;
		step(var);
		hit(worldMap, var);
		draw(var, data, var);
		var->x++;
	}
}

void	init_keys(var_t *var, int key_number)
{
	int *ptr;

	ptr = &var->ESC;
	while (key_number)
	{
		*ptr = 0;
		ptr++;
		key_number--;
	}
}

int		key_pressed(int keycode, var_t *var)
{
	if (keycode == 53)
	{
		var->ESC = 1;
		ft_putstr("\nESC = ");
		ft_putnbr(var->ESC);
	}
		
	else if (keycode == 13)
	{
		var->W = 1;
		ft_putstr("\nW = ");
		ft_putnbr(var->W);
	}
		
	else if (keycode == 0)
	{
		var->A = 1;
		ft_putstr("\nA = ");
		ft_putnbr(var->A);
	}
		
	else if (keycode == 1)
	{
		var->S = 1;
		ft_putstr("\nS = ");
		ft_putnbr(var->S);
	}
		
	else if (keycode == 2)
	{
		var->D = 1;
		ft_putstr("\nD = ");
		ft_putnbr(var->D);
	}
	return (0);	
}

int		key_released(int keycode, var_t *var)
{
	if (keycode == 53)
	{
		var->ESC = 0;
		ft_putstr("\nESC = ");
		ft_putnbr(var->ESC);
	}
		
	else if (keycode == 13)
	{
		var->W = 0;
		ft_putstr("\nW = ");
		ft_putnbr(var->W);
	}
		
	else if (keycode == 0)
	{
		var->A = 0;
		ft_putstr("\nA = ");
		ft_putnbr(var->A);
	}
		
	else if (keycode == 1)
	{
		var->S = 0;
		ft_putstr("\nS = ");
		ft_putnbr(var->S);
	}
		
	else if (keycode == 2)
	{
		var->D = 0;
		ft_putstr("\nD = ");
		ft_putnbr(var->D);
	}
	return (0);
}

int	main(void)
{
	int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	data_t data;
	var_t var;

	data.s_w = 640;
	data.s_h = 480;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, data.s_w, data.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	init_raycast(&var, &data, &var);
	raycast(&var, &data, &var, worldMap);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, var.img, 0, 0);
	init_keys(&var, 5);
	mlx_hook(data.mlx_win, 2, 2, key_pressed, &var);
	mlx_key_hook(data.mlx_win, key_released, &var);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}

