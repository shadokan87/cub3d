
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include "gnl_working/get_next_line.h"
#include "libft/libft.h"
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
	//var
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
	float step;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int wallx;
	int tex_y;
	int texpos;
	int tex_x;
	int tex_h;
	int tex_w;
	void *t_img;
	int *t_addr;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int *img_data;
	int color;
	int		ESC;
	int		W;
	int		A;
	int		S;
	int		D;
	int		L_R;
	int		R_R;
	void	*img;
	int t_endian;
	int t_bpp;
	int t_line;
	int	endian;
	int	bpp;
	int	line;
	int	offset;
	int	x;
	int	s_h;
	int	s_w;
	//
	char **text_paths;
	int **loaded_text;
	int **loaded_addr;
    char *paramFile;
    int F_color[3];
    int C_color[3];
    char **ParamSliced;
	
	//

	//
	double zBuffer[1200];
	int sX;
	int y;
	double spriteX;
	double spriteY;
	double sprite;
	double s_dirX;
	double s_dirY;
	double invd;
	double transformX;
	double transformY;
	int spriteScreenX;
	int spriteWidth;
	int spriteHeight;
	int drawStartX;
	int drawEndX;
	int drawStartY;
	int drawEndY;
	int texX;
	int texY;
	//
	char	*addr;
	void	*mlx_ptr;
    void	*mlx_win;
	int **map;
	int	o_drawStart;
	int o_drawEnd;
	int o_x;
}	var_t;

int		rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

char *Remove_extraSpaces(char *str)
{
    char *return_value;
    int i;
    int y;

    i = 0;
    y = 0;
    if (!(return_value = malloc(sizeof(char) * strlen(str))))
        return (0);
    while (str[i])
    {
        if (!(str[i] && str[i] == ' ' && str[i - 1] == ' '))
       {
        return_value[y] = str[i];
        y++;
       }
       i++;
    }
   printf("%s", return_value);
    return (return_value);
}

void    getParamFile(int fd, char **line, var_t *var)
{
    int ret;
	char *to_free;

    ret = 0;
    while ((ret = get_next_line(fd, line)) > 0)
       var->paramFile = ft_strjoin(var->paramFile ? var->paramFile : "", *line);
	// to_free = var->paramFile;
	// var->paramFile = Remove_extraSpaces(var->paramFile);
	// free(to_free);
}

int  ft_strcmp(char *str, char *str2)
{
    int i;

    i = 0;
    if (ft_strlen(str) != ft_strlen(str2))
        return (0);
    while (str[i])
    {
        if (str[i] == str2[i])
            i++;
        else
            return (0);
    }
    return (1);
}

void    fill_color(var_t *var, int i)
{
    if (ft_strcmp(var->ParamSliced[i], "F"))
    {
        var->F_color[0] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[0]);
        var->F_color[1] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[1]);
        var->F_color[2] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[2]);
        return ;         
    }
    var->C_color[0] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[0]);
    var->C_color[1] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[1]);
    var->C_color[2] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[2]);
}

void   fillLoopParams(var_t *var)
{
    int i;

    i = 0;
    while (var->ParamSliced[i] != NULL)
    {
        if (ft_strcmp(var->ParamSliced[i], "R"))
        {
            var->s_w = ft_atoi(var->ParamSliced[i + 1]);
            var->s_h = ft_atoi(var->ParamSliced[i + 2]);
        }
        if (ft_strcmp(var->ParamSliced[i], "NO"))
            var->text_paths[2] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "SO"))
            var->text_paths[3] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "WE"))
            var->text_paths[4] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "EA"))
            var->text_paths[5] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "S"))
            var->text_paths[6] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "F") || ft_strcmp(var->ParamSliced[i], "C"))
            fill_color(var, i);
		else if (i <= 8 &&i != 7)
			var->text_paths[i] = NULL;
        i++;
    }
} 

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
	//hit
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
		{
			var->hit = var->map[var->mapX][var->mapY];
			var->wallx = var->hit;
		}
			
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

void	draw_info(var_t *var)
{
	var->lineHeight = (int)(var->s_h / var->perpWallDist);
	var->drawStart = -var->lineHeight / 2 + var->s_h / 2;
	if (var->drawStart < 0)
		var->drawStart = 0;
	var->drawEnd = var->lineHeight / 2 + var->s_h / 2;
	if (var->drawEnd >= var->s_h)
		var->drawEnd = var->s_h - 1;
}

void	draw_sprite(var_t *var, int numSprites)
{
	int x;
	int y;
	double spriteX = var->spriteX - var->posX;
	double spriteY = var->spriteY - var->posY;

	double invDet = 1.0 / (var->planeX * var->dirY - var->dirX * var->planeY);

	double transformX = invDet * (var->dirY * spriteX - var->dirX * spriteY);
	double transformY = invDet * (-var->planeY * spriteX + var->planeX * spriteY);

	int spriteScreenX = (int)(((var->s_w / 2) * (1 + transformX / transformY)));

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
	x = drawStartX - 1;
	int t_bpp;
	int t_line;
	int t_endian;
	//var->loaded_addr[6] = (int *)mlx_get_data_addr("./barrel.XPM", &t_bpp, &t_line, &t_endian);
	while (++x < drawEndX)
	{
		if (transformY > 0 && x > 0 && x < var->s_w && transformY < var->zBuffer[x])
		{
			y = drawStartY - 1;
			int texX = (int)(256 * (x - (-spriteWidth / 2 + spriteScreenX)) * var->tex_w/ spriteWidth) / 256;

			while(++y < drawEndY)
			{
				int d = (y) * 256 - var->s_h * 128 + spriteHeight * 128;
				int texY = ((d * var->tex_h / spriteHeight) / 256);
				int color = var->loaded_addr[6][(texX + texY * var->tex_w)];
				if ((color & 0x00FFFFFF) != 0) pixel_put(var, x, y, color);
			}
		}
	}
	
}



void	draw_texture(var_t *var)
{
	draw_info(var);
	int texx;
	int texy;
	double wallx;
	double step;
	double texpos;


	if (var->hit == 6)
		return ;
	if (var->side == 0)
		wallx = var->posY + var->perpWallDist * var->rayDirY;
	else
		wallx = var->posX + var->perpWallDist * var->rayDirX;
	wallx -= floor(wallx);

	texx = (int)(wallx * (double)var->tex_w);
	if (var->side == 0 && var->rayDirX > 0)
		texx = var->tex_w - texx - 1;
	if (var->side == 1 && var->rayDirY < 0)
		texx = var->tex_w - texx - 1;
	
	step = 1.0 * var->tex_h / var->lineHeight;
	texpos = (var->drawStart - var->s_h / 2 + var->lineHeight / 2) * step;
	char *dst;
	int color;
	while (var->drawStart < var->drawEnd)
	{
		dst = var->addr + (var->drawStart * var->line + var->x * (var->bpp / 8));
		texy = (int)texpos;
		texpos += step;
		//*(unsigned int*)dst = color;
		pixel_put(var, var->x, var->drawStart, var->loaded_addr[var->hit][64 * texy + texx]);
		var->drawStart++;
	}

}

void	draw(var_t *var)
{
	draw_info(var);
	var->color = 255;
	if (var->side == 1)
		var->color = var->color / 2;
		verline(var, var->x, var->drawStart, var->drawEnd, var->color);
}



void	raycast(var_t *var)
{
	//ray
	var->x = 0;
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
		verline(var, var->x, 0, var->s_h / 2, rgb_int(var->C_color[0], var->C_color[1], var->C_color[2]));
		verline(var, var->x, var->s_h / 2, var->s_h, rgb_int(var->F_color[0], var->F_color[1], var->F_color[2]));
		if (var->hit == 1)
			draw(var);
		if (var->hit > 1)
			draw_texture(var);
		var->zBuffer[var->x] = var->perpWallDist;
		var->x++;
		
	}
	draw_sprite(var, 1);
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

int	**duplicate_map(int worldMap[mapWidth][mapHeight], var_t *var)
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
	if (map[y][i] == 6)
	{
		var->spriteX = i;
		var->spriteY = y;
	}
    i++;
  }
  i = 0;
  y++;
  } 
	return (map);
}

int	load_text(var_t *var)
{
	int i;
	int t_endian;
	int t_bpp;
	int t_line;

	i = 2;
	if (!(var->loaded_text = malloc(sizeof(int *) * 9)))
		return (0);
	if (!(var->loaded_addr = malloc(sizeof(int *) * 9)))
		return (0);
	while (i <= 6)
	{
		if (var->text_paths[i])
		{
			if (i == 6)
				ft_putstr(var->text_paths[i]);
			var->loaded_text[i] = mlx_xpm_file_to_image(var->mlx_ptr, var->text_paths[i], &var->tex_w, &var->tex_h);
			var->loaded_addr[i] = (int *)mlx_get_data_addr(var->loaded_text[i], &t_bpp, &t_line, &t_endian);
		}
		i++;
	}
}

int		run(var_t *var)
{
	int t_endian;
	int t_bpp;
	int t_line;

	var->tex_h = 64;
	var->tex_w = 64;
	var->img_data = (int *)mlx_get_data_addr(var->img, &var->t_bpp, &var->t_line, &var->t_endian);
	listen_keys(var);
	if (var->S || var->W || var->D || var->A
	|| var->R_R || var->L_R)
		cls(var);
	raycast(var);
	mlx_put_image_to_window(var->mlx_ptr, var->mlx_win, var->img, 0, 0);
}

int		start(var_t *var)
{
	load_text(var);
	mlx_loop_hook(var->mlx_ptr, run, (void *)var);
	mlx_loop(var->mlx_ptr);
}

void	init_struct(var_t *var, char **argv)
{
	int fd;
    char *line;
    int i = 0;
    int y = 0;

    var->paramFile = NULL;
	var->ParamSliced = NULL;
    fd = open(argv[1], O_RDONLY);
    getParamFile(fd, &line, var);
    i = 0;
    while (var->paramFile[i])
    {
        if (var->paramFile[i] == '\n')
            var->paramFile[i] = ' ';
        i++;
    }
    i = 0;
    var->ParamSliced = ft_split(var->paramFile, ' ');
    if (!(var->text_paths = malloc(sizeof(char *) * 9)))
        return ;
	fillLoopParams(var);
}

int	main(int argc, char **argv)
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
  {1,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,1},
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

	init_struct(&var, argv);
	if ((var.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((var.mlx_win = mlx_new_window(var.mlx_ptr, var.s_w, var.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	var.map = duplicate_map(worldMap, &var);
	init_raycast(&var);
	init_keys(&var, 5);
	start(&var);
	return (EXIT_SUCCESS);
}