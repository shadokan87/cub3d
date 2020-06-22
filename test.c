#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct s_var
{
    void          *mlx_ptr;
    void          *mlx_win;
    int tex_h;
    int tex_w;
    int s_w;
    int s_h;
    int endian;
    int bpp;
    int line;
    int t_endian;
    int t_bpp;
    int t_line;
    char *addr;
    int *t_addr;
    void *t_img;
    void *img;
}   var_t;

int main(void)
{
    var_t var;
    
    var.tex_h = 64;
    var.tex_w = 64;
    var.s_h = 480;
    var.s_w = 640;

    if ((var.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((var.mlx_win = mlx_new_window(var.mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    var.img = mlx_new_image(var.mlx_ptr, var.s_w, var.s_h);
    var.addr = mlx_get_data_addr(var.img, &var.bpp, &var.line, &var.endian);
    var.t_img = mlx_xpm_file_to_image(var.mlx_ptr, "bluestone.xpm", &var.tex_w, &var.tex_h);
    var.t_addr = (int *)mlx_get_data_addr(var.t_img, &var.t_bpp, &var.t_line, &var.t_endian);
    char *dst;
    int x;
    int y;
    int color;

    x = 0;
    y = 0;
    while (y < 64)
    {
        while (x < 64)
        {
            dst = var.img + (y * var.line + x * (var.bpp / 8));
            *(unsigned int*)dst = var.t_addr[64 * y + x];
            x++;
        }
        y++;
        x = 0;
    }

    
    mlx_put_image_to_window(var.mlx_ptr, var.mlx_win, var.img, 0, 0);
    mlx_loop(var.mlx_ptr);
    return (EXIT_SUCCESS);
}

void	draw_sprite(var_t *var, int numSprites)
{
	int i = 0;
	double spriteX;
	double spriteY;
	int texWidth = 40;
	int texHeight = 40;
	while (i < numSprites)
	{
		spriteX = var->spriteX - var->posX;
		spriteY = var->spriteY - var->posY;
		double invDet = 1.0 / (var->planeX * var->dirY - var->dirX * var->planeY);
		
		double transformX = invDet * (var->dirY * spriteX - var->dirX * spriteY);
		double transformY = invDet * (-var->planeY * spriteX * var->planeX * spriteY);

		int spriteScreenX = (int)((var->s_w / 2) * (1 + transformX / transformY));

		int spriteHeight = abs((int)(var->s_h / (transformY)));
		int drawStartY = -spriteHeight / 2 + var->s_h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + var->s_h / 2;
		if (drawEndY >= var->s_h)
			drawEndY = var->s_h - 1;
		int spriteWidth = abs((int)(var->s_h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= var->s_w)
			drawEndX = var->s_w - 1;
		int stripe = 0;
		while (stripe < drawStartX)
		{
			int texX = (int)(256 * (stripe - (spriteWidth / 2 + spriteScreenX) * texWidth / spriteWidth) / 256);
			if (transformY > 0 && stripe > 0 && stripe < var->s_w)
			{
				int y = 0;
				while (y < drawStartY)
				{
					int d = (y) * 256 - var->s_h * 128 + spriteHeight * 128;
					int texY = ((d * texHeight) / spriteHeight) / 256;
					//pixel_put(var, var->x, var->drawStart, var->loaded_addr[var->hit][64 * texy + texx]);
					int color = var->loaded_addr[6][texWidth * texY * texX];
					if ((color & 0x00FFFFFF) != 0)
						pixel_put(var, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		
		i++;
	}
}