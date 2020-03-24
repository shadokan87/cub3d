#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

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

void	init_raycast(pixel_info_t *pixel, data_t *data)
{
	pixel->s_w = data->s_w;
	pixel->s_h = data->s_h;
	pixel->img = mlx_new_image(data->mlx_ptr, data->s_w, data->s_h);
	pixel->addr = mlx_get_data_addr(pixel->img, &pixel->bpp, &pixel->line, &pixel->endian);

}

int	main(void)
{
	data_t data;
	pixel_info_t pixel;

	data.s_w = 640;
	data.s_h = 480;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, data.s_w, data.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	init_raycast(&pixel, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, pixel.img, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
