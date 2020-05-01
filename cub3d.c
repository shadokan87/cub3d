#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>

#define rotSpeed 0.02
#define moveSpeed 0.1
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
	int		L_R;
	int		R_R;
	void	*img;
	int	endian;
	int	bpp;
	int	line;
	int	offset;
	int	x;
	int	s_h;
	int	s_w;
	char	*addr;
	void	*mlx_ptr;
    void	*mlx_win;
	int **map;
	int	o_drawStart;
	int o_drawEnd;
	int o_x;
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

void	init_raycast(var_t *var)
{
	var->s_w = var->s_w;
	var->s_h = var->s_h;
	var->img = mlx_new_image(var->mlx_ptr, var->s_w, var->s_h);
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

void	hit(var_t *var)
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
		if (var->map[var->mapX][var->mapY] > 0)
			var->hit = 1;
	}
	if (var->side == 0)
		var->perpWallDist = (var->mapX - var->posX + (1 - 
		var->stepX) / 2) / var->rayDirX;
	else
		var->perpWallDist = (var->mapY - var->posY + (1 - var->stepY) / 2) / var->rayDirY;	
}

void	cls(var_t *var)
{
	int x = 0;
	while (x < var->s_w)
	{
		verline(var, x, 0, var->s_h, 0);
		x++;
	}
}

void	draw(var_t *var)
{
	var->lineHeight = (int)(var->s_h / var->perpWallDist);
	var->drawStart = -var->lineHeight / 2 + var->s_h / 2;
	if (var->drawStart < 0)
		var->drawStart = 0;
	var->drawEnd = var->lineHeight / 2 + var->s_h / 2;
	if (var->drawEnd >= var->s_h)
		var->drawEnd = var->s_h - 1;
	var->color = 255;
	if (var->side == 1)
		var->color = var->color / 2;
	verline(var, var->x, var->drawStart, var->drawEnd, var->color);
}

void	raycast(var_t *var)
{
	var->x = 0;
	if (var->S || var->W || var->D || var->A
	|| var->R_R || var->L_R)
		cls(var);
	while (var->x < var->s_w)
	{
		var->cameraX = 2 * var->x / (double)var->s_w - 1;
		var->rayDirX = var->dirX + var->planeX * var->cameraX;
		var->rayDirY = var->dirY + var->planeY * var->cameraX;
		var->mapX = (int)var->posX;
		var->mapY = (int)var->posY;
		var->deltaDistX = fabs(1 / var->rayDirX);
		var->deltaDistY = fabs(1 / var->rayDirY);
		var->hit = 0;
		step(var);
		hit(var);
		draw(var);
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
	else if (keycode == 123)
	{
		var->L_R = 1;
		ft_putstr("\nL_R = ");
		ft_putnbr(var->L_R);
	}
	else if (keycode == 124)
	{
		var->R_R = 1;
		ft_putstr("\nR_R = ");
		ft_putnbr(var->R_R);
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
	else if (keycode == 123)
	{
		var->L_R = 0;
		ft_putstr("\nL_R = ");
		ft_putnbr(var->L_R);
	}
	else if (keycode == 124)
	{
		var->R_R = 0;
		ft_putstr("\nR_R = ");
		ft_putnbr(var->R_R);
	}
	return (0);
}

int	move_is_possible(int pos)
{
	if (pos == 1 || pos == 4)
		return (0);
	return (1);
}

void	fwd_bckwrd(var_t *var)
{
// if (var->W)
//     {
// 		if (move_is_possible(var->map[(int)(var->posX + var->dirX * moveSpeed)]
//                          [(int)(var->posX)]))
//                          var->posX += var->dirX * moveSpeed * 0.5;
//     }
if (var->W)
    {
      if(var->map[(int)(var->posX + var->dirX * moveSpeed)][(int)(var->posY)] == 0) 
	  	var->posX += var->dirX * moveSpeed * 0.5;
      if(var->map[(int)(var->posX)][(int)(var->posY + var->dirY * moveSpeed)] == 0)
	  	var->posY += var->dirY * moveSpeed * 0.5;
    }
	if (var->S)
	{
		if (var->map[(int)(var->posX - var->dirX * moveSpeed)]
                         [(int)(var->posY)] == 0)
                         var->posX -= var->dirX * moveSpeed * 0.5;
		if (var->map[(int)(var->posX)][(int)(var->posY - var->dirY * moveSpeed)] == 0)
			var->posY -= var->dirY * moveSpeed * 0.5;
	}
}

void	x_y(var_t *var)
{
if (var->A)
	{
		if (var->map[(int)(var->posX)][(int)(var->posY + var->dirX * moveSpeed)] == 0)
			var->posY += var->dirX * moveSpeed * 0.5;
		if (var->map[(int)(var->posX - var->dirY * moveSpeed)][(int)(var->posY)] == 0)
			var->posX -= var->dirY * moveSpeed * 0.5;
	}
	if (var->D)
	{
		if (var->map[(int)(var->posX)][(int)(var->posY - var->dirX * moveSpeed)] == 0)
			var->posY -= var->dirX * moveSpeed * 0.5;
		if (var->map[(int)(var->posX + var->dirY * moveSpeed)][(int)(var->posY)] == 0)
			var->posX += var->dirY * moveSpeed * 0.5;
	}
}

void	l_r(var_t *var)
{
	double old_dir;
	double old_plane;
	double rot_speed;

	old_dir = var->dirX;
	old_plane = var->planeX;
	rot_speed = 0.1;
	if (var->R_R)
	{
		var->dirX = (var->dirX * cos(-rotSpeed)) - var->dirY * sin(-rotSpeed);
		var->dirY = (old_dir * sin(-rotSpeed) + var->dirY * cos(-rotSpeed));
		var->planeX = (var->planeX * cos(-rotSpeed) - var->planeY * sin(-rotSpeed));
     	var->planeY = (old_plane * sin(-rotSpeed) + var->planeY * cos(rotSpeed));
	}
	if (var->L_R)
	{
		var->dirX = (var->dirX * cos(rotSpeed)) - var->dirY * sin(rotSpeed);
		var->dirY = (old_dir * sin(rotSpeed) + var->dirY * cos(rotSpeed));
		var->planeX = (var->planeX * cos(rotSpeed) - var->planeY * sin(rotSpeed));
     	var->planeY = (old_plane * sin(rotSpeed) + var->planeY * cos(rotSpeed));
	}
}

int	movement(var_t *var)
{
	fwd_bckwrd(var);
	x_y(var);
	l_r(var);
}

int	listen_keys(var_t *var)
{
	mlx_hook(var->mlx_win, 2, 2, key_pressed, (void *)var);
	mlx_key_hook(var->mlx_win, key_released, (void *)var);
	movement(var);
}

int	**duplicate_map(int worldMap[mapWidth][mapHeight])
{
	int **map;
	int i;
	int y;
	
	i = 0;
	y = 0;
	map = malloc(sizeof(int *) * 24);
	while (i < 24)
  {
    map[i] = malloc(sizeof(int) * 24);
    i++;
  }
  i = 0;
  while (y < 24)
  {
    while (i < 24)
  {
    map[y][i] = worldMap[y][i];
    i++;
  }
  i = 0;
  y++;
  } 
	return (map);
}

int		run(var_t *var)
{
	listen_keys(var);
	raycast(var);
	mlx_put_image_to_window(var->mlx_ptr, var->mlx_win, var->img, 0, 0);
}

int		start(var_t *var)
{
	mlx_loop_hook(var->mlx_ptr, run, (void *)var);
	mlx_loop(var->mlx_ptr);
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
  {1,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,1},
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
	var_t var;

	var.s_w = 640;
	var.s_h = 480;
	if ((var.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((var.mlx_win = mlx_new_window(var.mlx_ptr, var.s_w, var.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	var.map = duplicate_map(worldMap);
	init_raycast(&var);
	init_keys(&var, 5);
	start(&var);
	return (EXIT_SUCCESS);
}

