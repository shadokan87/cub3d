#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24

typedef struct    data_s
{
    void	*mlx_ptr;
    void	*mlx_win;
    int		s_w;
    int		s_h;
    
}                 data_t;

typedef struct	pixel_put_s
{
	void	*img;
	int	endian;
	int	bpp;
	int	line;
	int	offset;
	int	x;
	int	s_h;
	int	s_w;
	char	*addr;
}	pixel_info_t;

typedef struct double_var_s
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

}	dbl_t;

typedef struct integer_var_s
{
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
}	int_t;

void	pixel_put(pixel_info_t *pixel, int x, int y, int color)
{
	char *dst;

	dst = pixel->addr + (y * pixel->line + x * (pixel->bpp / 8));
	*(unsigned int*)dst = color;
}

int	verline(pixel_info_t *pixel, int x, int draw_start, int draw_end, int color)
{
	int swap;

	if (draw_end < draw_start)
	{
		swap = draw_start;
		draw_start = draw_end;
		draw_end = swap;
	}
	if (draw_end < 0 || draw_start >= pixel->s_h || x < 0 || x >= pixel->s_w)
		return (0);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= pixel->s_w)
		draw_end = pixel->s_h - 1;
	while (draw_start < draw_end)
	{
		pixel_put(pixel, x, draw_start, color);
		draw_start++;
	}
	return (1);
}

void	init_raycast(pixel_info_t *pixel, data_t *data, dbl_t *dbl)
{
	pixel->s_w = data->s_w;
	pixel->s_h = data->s_h;
	pixel->img = mlx_new_image(data->mlx_ptr, data->s_w, data->s_h);
	pixel->addr = mlx_get_data_addr(pixel->img, &pixel->bpp, &pixel->line, &pixel->endian);
	dbl->posX = 22;
	dbl->posY = 12;
	dbl->dirX = -1;
	dbl->dirY = 0;
	dbl->planeX = 0;
	dbl->planeY = 0.66;
	dbl->time = 0;
	dbl->oldTime = 0;

}

void	step(dbl_t *dbl, int_t *integ)
{
	if (dbl->rayDirX < 0)
	{
		integ->stepX = -1;
		dbl->sideDistX = (dbl->posX - integ->mapX) * dbl->deltaDistX;
	}
	else
	{
		integ->stepX = 1;
		dbl->sideDistX = (integ->mapX + 1.0 - dbl->posX) * dbl->deltaDistX;
	}
	if (dbl->rayDirY < 0)
	{
		integ->stepY = -1;
		dbl->sideDistY = (dbl->posY - integ->mapY) * dbl->deltaDistY;
	}
	else
	{
		integ->stepY = 1;
		dbl->sideDistY = (integ->mapY + 1.0 - dbl->posY) * dbl->deltaDistY;
	}
}

void	hit(int worldMap[mapWidth][mapHeight], dbl_t *dbl, int_t *integ)
{
	while (integ->hit == 0)
	{
		if (dbl->sideDistX < dbl->sideDistY)
		{
			dbl->sideDistX += dbl->deltaDistX;
			integ->mapX += integ->stepX;
			integ->side = 0;
		}
		else
		{
			dbl->sideDistY += dbl->deltaDistY;
			integ->mapY += integ->stepY;
			integ->side = 1;
		}
		if (worldMap[integ->mapX][integ->mapY] > 0)
			integ->hit = 1;
	}
	if (integ->side == 0)
		dbl->perpWallDist = (integ->mapX - dbl->posX + (1 - 
		integ->stepX) / 2) / dbl->rayDirX;
	else
		dbl->perpWallDist = (integ->mapY - dbl->posY + (1 - integ->stepY) / 2) / dbl->rayDirY;	
}

void	draw(data_t *data, dbl_t *dbl, int_t *integ, pixel_info_t *pixel)
{
	integ->lineHeight = (int)(data->s_h / dbl->perpWallDist);
	integ->drawStart = -integ->lineHeight / 2 + data->s_h / 2;
	if (integ->drawStart < 0)
		integ->drawStart = 0;
	integ->drawEnd = integ->lineHeight / 2 + data->s_h / 2;
	if (integ->drawEnd >= data->s_h)
		integ->drawEnd = data->s_h - 1;
	integ->color = 255;
	if (integ->side == 1)
		integ->color = integ->color / 2;
	verline(pixel, pixel->x, integ->drawStart, integ->drawEnd, integ->color);
}

void	raycast(pixel_info_t *pixel, data_t *data, dbl_t *dbl, int_t *integ,
int worldMap[mapWidth][mapHeight])
{
	pixel->x = 0;
	while (pixel->x < data->s_w)
	{
		dbl->cameraX = 2 * pixel->x / (double)data->s_w - 1;
		dbl->rayDirX = dbl->dirX + dbl->planeX * dbl->cameraX;
		dbl->rayDirY = dbl->dirY + dbl->planeY * dbl->cameraX;
		integ->mapX = (int)dbl->posX;
		integ->mapY = (int)dbl->posY;
		dbl->deltaDistX = fabs(1 / dbl->rayDirX);
		dbl->deltaDistY = fabs(1 / dbl->rayDirY);
		integ->hit = 0;
		step(dbl, integ);
		hit(worldMap, dbl, integ);
		draw(data, dbl, integ, pixel);
		pixel->x++;
	}
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
	pixel_info_t pixel;
	dbl_t dbl;
	int_t integ;

	data.s_w = 640;
	data.s_h = 480;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, data.s_w, data.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	init_raycast(&pixel, &data, &dbl);
	raycast(&pixel, &data, &dbl, &integ, worldMap);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, pixel.img, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
