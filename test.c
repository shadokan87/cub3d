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