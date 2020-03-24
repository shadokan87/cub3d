#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>


#define mapWidth 24
#define mapHeight 24

//KEYS
#define SDLK_ESCAPE '\033'

typedef struct    data_s
{
void	*mlx_ptr;
void	*mlx_win;
void	*img;
char	*addr;
int	bpp;
int	endian;
int	ll;
int	offset;
int	screen_height;
int	screen_width;
int	x;

}                 data_t;

int		create_trgb(int t, int r, int g, int b)
{
	return(b << 24 | g << 16 | r << 8 | t);
}

void    pixel_put(data_t *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->ll + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int	verline(data_t *data, int x, int draw_start, int draw_end, int color)
{
	int swap;

	if (draw_end < draw_start)
	{
		swap = draw_start;
		draw_start = draw_end;
		draw_end = swap;
	}
	if (draw_end < 0 || draw_start >= data->screen_height || x < 0 || x >= data->screen_width)
		return (0);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= data->screen_width)
		draw_end = data->screen_height - 1;
	while (draw_start < draw_end)
	{
		pixel_put(data, x, draw_start, color);
		draw_start++;
	}
	return (1);
}

int main(void)
{
    data_t        data;

    data.screen_height = 480;
    data.screen_width = 640;
	if ((data.mlx_ptr = mlx_init()) == NULL)
        	return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, data.screen_width,	data.screen_height, "Hello world")) == NULL)
        	return (EXIT_FAILURE);
    data.img = mlx_new_image(data.mlx_ptr, data.screen_width, data.screen_height);
    data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ll, &data.endian);
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
double posX = 22;
double posY = 12;
double dirX = -1;
double dirY = 0;
double planeX = 0;
double planeY = 0.66;
double time = 0;
double oldTime = 0;

data.x = 0;
       while (data.x < data.screen_width)
   {
   	double cameraX = 2 * data.x / (double)data.screen_width - 1;
	double rayDirX = dirX + planeX * cameraX;
	double rayDirY = dirY + planeY * cameraX;

	int mapX = (int)posX;
	int mapY = (int)posY;

	double sideDistX;
	double sideDistY;

	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	double perpWallDist;

	int stepX;
	int stepY;

	int hit = 0;
	int side;
	
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
	stepX = 1;
	sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (worldMap[mapX][mapY] > 0)
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
	int lineHeight = (int)(data.screen_height / perpWallDist);
	int drawStart = -lineHeight / 2 + data.screen_height / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + data.screen_height / 2;
	if (drawEnd >= data.screen_height)
		drawEnd = data.screen_height - 1;
	int color = 255;
	if (side == 1)
		color = color / 2;
	verline(&data, data.x, drawStart, drawEnd, color);
	data.x++;
   }
mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.img, 0, 0);

    mlx_loop(data.mlx_ptr);
}
