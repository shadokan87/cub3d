
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include "gnl_working/get_next_line.h"
//#include "libft/libft.h"
#include "printf/lprintf.h"
#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>

#define rotSpeed 0.1
#define moveSpeed 0.1

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
	int screenshot;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int wallx;
	int ompx;
	int ompy;
	int tex_y;
	int texpos;
	int tex_x;
	int tex_h;
	int tex_w;
	int **spriteQueue;
	int *queue;
	double *dist;
	void *t_img;
	int *t_addr;
	int spriteHit;
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
	int m_width;
	int m_height;
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
	double zBuffer[10000];
	int y;
	int spriteNum;
	int *sX;
	int *sY;
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
	int *spriteorder;
	//
	char	*addr;
	void	*mlx_ptr;
    void	*mlx_win;
	int **map;
	int	o_drawStart;
	int o_drawEnd;
	int o_x;
}	var_t;

void    *ft_memset(void *b, int c, size_t len)
{
        unsigned long   i_array_b;
        unsigned char   *a;

        i_array_b = 0;
        a = (unsigned char *)b;
        while (i_array_b < len)
        {
                a[i_array_b] = (unsigned char)c;
                i_array_b++;
        }
        b = a;
        return (b);
}

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
    return (return_value);
}

int	isWall(char c)
{
	if (c == '4')
		return (1);
	else if (c == '5')
		return (5);
	else if (c == '3')
		return (3);
	else if (c == '2')
		return (2);
	else if (c == '1')
		return (1);
	return (0);
}

int	getMapIndex(var_t *var)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (var->paramFile && var->paramFile[i])
	{
		if (isWall(var->paramFile[i]) && var->paramFile[i + 1] == ' ' && isWall(var->paramFile[i + 2]))
			return (i);
		i++;
	}
	return (-1);
}

int     ft_tolower(int c)
{
        if (c >= 'A' && c <= 'Z')
                return (c + 32);
        return (c);
}

int	NoSpaceGetMapIndex(char *str)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (isWall(str[i]) && isWall(str[i + 2]) && isWall(str[i + 3]))
			return (1);
		i++;
	}
	return (-1);
}

char *removeS(char *str, var_t *var)
{
	int i = 0;

	while (str[i])
	{
		if (getMapIndex(var) != -1)
		{
			if (str[i] == 'S')
				str[i] = '3';
			else if (str[i] == 'N')
				str[i] = '2';
			else if (str[i] == 'W')
				str[i] = '4';
			else if (str[i] == '2')
				str[i] = '6';
			else if (str[i] == 'E')
				str[i] = '5';
		}
		//str[i] = ft_tolower(str[i]);		
		i++;
	}
	return (str);
}

void    getParamFile(int fd, char **line, var_t *var)
{
    int ret;
	int i;
	char *to_free;
	char *str;

//ft_printf("-->%d\n", (int)'s');
    ret = 0;
	i = 0;
    while ((ret = get_next_line(fd, line)) > 0)
	{	
			*line = removeS(*line, var);
			//ft_printf("%s", *line);
		var->paramFile = ft_strjoin(var->paramFile ? var->paramFile : "", *line);
	}
		
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
if (ft_strcmp(var->ParamSliced[i], "r"))
        {
            var->s_w = ft_atoi(var->ParamSliced[i + 1]);
            var->s_h = ft_atoi(var->ParamSliced[i + 2]);
        }
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

int	distIsSorted(var_t *var, double *dist)
{

}

void	swapQueueRev(var_t *var, double *dist)
{
	int i;
	double swap;
	int x;
	int y;

	x = 0;
	y = 0;
	i = 1;

	//ft_printf("rev");
	while (i < var->spriteNum)
	{
		if (dist[i - 1] < dist[i])
		{//ft_printf("here");
			swap = dist[i - 1];
			dist[i - 1] = dist[i];
			dist[i] = swap;
			x = var->spriteQueue[i - 1][0];
			y = var->spriteQueue[i - 1][1];
			var->spriteQueue[i - 1][0] = var->spriteQueue[i][0];
			var->spriteQueue[i - 1][1] = var->spriteQueue[i][1];
			var->spriteQueue[i][0] = x;
			var->spriteQueue[i][1] = y;
			i = 1;
			x = 0;
			y = 0;
		}
		else
			i++;
		
	}
}

int *cpy(var_t *var, int *tab)
{
	int *ret = malloc(sizeof(int) * 2);
	ret[0] = tab[0];
	ret[1] = tab[1];
	return (ret);
}

void	swapQueue(var_t *var, double *dist)
{

	int i = 0;
	int x;
	int y;

	int *swap;

	// swap = cpy(var, var->spriteQueue[0]);
	// var->spriteQueue[0] = cpy(var, var->spriteQueue[1]);
	// var->spriteQueue[1] = cpy(var, swap);
 	// int i;
	// double swap;
	// int x;
	// int y;

	// x = 0;
	// y = 0;
	// i = 1;
	// //printf("d");
	// //ft_printf("normal %d\n", distIsSorted(var, dist));
	// ft_printf("here");
	// while (i < var->spriteNum)
	// {
	// 	if (dist[i - 1] > dist[i])
	// 	{//ft_printf("here");
	// 		swap = dist[i - 1];
	// 		dist[i - 1] = dist[i];
	// 		dist[i] = swap;
	// 		x = var->spriteQueue[i - 1][0];
	// 		y = var->spriteQueue[i - 1][1];
	// 		var->spriteQueue[i - 1][0] = var->spriteQueue[i][0];
	// 		var->spriteQueue[i - 1][1] = var->spriteQueue[i][1];
	// 		var->spriteQueue[i][0] = x;
	// 		var->spriteQueue[i][1] = y;
	// 		i = 1;
	// 		x = 0;
	// 		y = 0;
	// 	}
	// 	else
	// 		i++;
		
	// }
}

double	*getDist(var_t *var)
{
	int i;
	double *dist;
	double swap;
	int swap2;

	dist = (double *)malloc(sizeof(double) * var->spriteNum);
	var->spriteorder = malloc(sizeof(int) * var->spriteNum);
	i = 0;
	while (i < var->spriteNum)
	{
		dist[i] = ((var->posX - var->spriteQueue[i][0]) *
		(var->posX - var->spriteQueue[i][0])
		+ (var->posY - var->spriteQueue[i][1])
		* (var->posY - var->spriteQueue[i][1]));
		var->spriteorder[i] = i;
		i++;
	}
	i = 1;
	while (i < var->spriteNum)
	{
		if (dist[i - 1] < dist[i])
		{
			swap = dist[i - 1];
			dist[i - 1] = dist[i];
			dist[i] = swap;
			swap2 = var->spriteorder[i - 1];
			var->spriteorder[i - 1] = var->spriteorder[i];
			var->spriteorder[i] = swap2;
			i = 1;
 		}
		 else
		 i++;
	}
	return (dist);
}

// void	swapQ(var_t *var)
// {
// 	int i;
// 	int y;
// 	int swap2;
// 	int swap3;
// 	double swap;

// 	i = 1;
// 	y = i + 1;
// 	while (i < var->spriteNum)
// 	{
// 		if (var->dist[i] > var->dist[i - 1])
// 		{
// 			//printf("test");
// 			swap = var->dist[i - 1];
// 			var->dist[i - 1] = var->dist[i];
// 			var->dist[i] = swap;
// 			swap2 = var->queue[y - 2];
// 			var->queue[y - 2] = var->queue[y];
// 			var->queue[y] = swap2;
// 			y++;
// 			swap2 = var->queue[y - 2];
// 			var->queue[y - 2] = var->queue[y];
// 			var->queue[y] = swap2;
// 			i = 1;
// 			y = i + 1;
//  		}
// 		else
// 		i++;
// 		y = i + 3;
// 	}
// }

int	**sortQueue(var_t *var)
{
	var->dist = getDist(var);
}

void	draw_sprite(var_t *var, int sx, int sy)
{
	int x;
	int y;
	double vMove = 0.0;
	double spriteX = sx - var->posX;
	double spriteY = sy - var->posY;

	double invDet = 1.0 / (var->planeX * var->dirY - var->dirX * var->planeY);

	double transformX = invDet * (var->dirY * spriteX - var->dirX * spriteY);
	double transformY = invDet * (-var->planeY * spriteX + var->planeX * spriteY);
	int vMoveScreen = (int)(vMove / transformY);

	int spriteScreenX = (int)((var->s_w / 2 * (1 + transformX / transformY)));

	int spriteHeight = abs((int)(var->s_h / (transformY)));

	int drawStartY = -spriteHeight / 2 + var->s_h / 2 + vMoveScreen;
	if (drawStartY < 0)
		drawStartY = 0;
	int drawEndY = spriteHeight / 2 + var->s_h / 2 + vMoveScreen;
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
	while (++x < drawEndX)
	{
		if (transformY > 0 && x > 0 && x < var->s_w && transformY < var->zBuffer[x])
		{
			y = drawStartY - 1;
			int texX = (int)(256 * (x - (-spriteWidth / 2 + spriteScreenX)) * var->tex_w/ spriteWidth) / 256;

			while(++y < drawEndY)
			{
				int d = (y - vMoveScreen) * 256 - var->s_h * 128 + spriteHeight * 128;
				int texY = ((d * var->tex_h / spriteHeight) / 256);
				int color = var->loaded_addr[6][(texX + texY * var->tex_w)];
				if ((color & 0x00FFFFFF) != 0) pixel_put(var, x, y, color);
			}
		}
	}	
}

// void	draw_sprite(var_t *var)
// {
// 	int z = 0;;

// 	while (z < var->spriteNum)
// 	{
// 	int x;
// 	int y;
// 	double vMove = 0.0;
// 	double spriteX = var->spriteQueue[z][0] - var->posX;
// 	double spriteY = var->spriteQueue[z][1] - var->posY;
// 	printf("%d %d\n", var->spriteQueue[z][0], var->spriteQueue[z][1]);

// 	double invDet = 1.0 / (var->planeX * var->dirY - var->dirX * var->planeY);

// 	double transformX = invDet * (var->dirY * spriteX - var->dirX * spriteY);
// 	double transformY = invDet * (-var->planeY * spriteX + var->planeX * spriteY);
// 	int vMoveScreen = (int)(vMove / transformY);

// 	int spriteScreenX = (int)((var->s_w / 2 * (1 + transformX / transformY)));

// 	int spriteHeight = abs((int)(var->s_h / (transformY)));

// 	int drawStartY = -spriteHeight / 2 + var->s_h / 2 + vMoveScreen;
// 	if (drawStartY < 0)
// 		drawStartY = 0;
// 	int drawEndY = spriteHeight / 2 + var->s_h / 2 + vMoveScreen;
// 	if (drawEndY >= var->s_h)
// 		drawEndY = var->s_h - 1;

// 	int spriteWidth = abs((int)(var->s_h / (transformY)));
// 	int drawStartX = -spriteWidth / 2 + spriteScreenX;
// 	if (drawStartX < 0)
// 		drawStartX = 0;
// 	int drawEndX = spriteWidth / 2 + spriteScreenX;
// 	if (drawEndX >= var->s_w)
// 		drawEndX = var->s_w - 1;
// 	x = drawStartX - 1;
// 	int t_bpp;
// 	int t_line;
// 	int t_endian;
// 	while (++x < drawEndX)
// 	{
// 		if (transformY > 0 && x > 0 && x < var->s_w && transformY < var->zBuffer[x])
// 		{
// 			y = drawStartY - 1;
// 			int texX = (int)(256 * (x - (-spriteWidth / 2 + spriteScreenX)) * var->tex_w/ spriteWidth) / 256;

// 			while(++y < drawEndY)
// 			{
// 				int d = (y - vMoveScreen) * 256 - var->s_h * 128 + spriteHeight * 128;
// 				int texY = ((d * var->tex_h / spriteHeight) / 256);
// 				int color = var->loaded_addr[6][(texX + texY * var->tex_w)];
// 				if ((color & 0x00FFFFFF) != 0) pixel_put(var, x, y, color);
// 			}
// 		}
// 	}	
// 		z++;
// 	}
// }

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

void	draw_texture(var_t *var)
{
	draw_info(var);
	int texx;
	int texy;
	double wallx;
	double step;
	double texpos;
		
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
	var->color = rgb_int(185, 94, 255);
	if (var->side == 1)
		var->color = var->color / 2;
		verline(var, var->x, var->drawStart, var->drawEnd, var->color);
}

void	raycast(var_t *var)
{
	//ray
	var->x = 0;
	int i = 0;
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
		var->spriteHit = 0;
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
			ft_printf("---->%s |%d|\n", var->text_paths[i],i);
			// if (i == 6)
			// 	ft_putstr(var->text_paths[i]);
			var->loaded_text[i] = mlx_xpm_file_to_image(var->mlx_ptr, var->text_paths[i], &var->tex_w, &var->tex_h);
			var->loaded_addr[i] = (int *)mlx_get_data_addr(var->loaded_text[i], &t_bpp, &t_line, &t_endian);
		}
		else
		ft_printf("ERR: --> %d\n", i);
		i++;
	}
}

static int
	get_color(var_t *var, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(var->mlx_ptr
			+ (4 * (int)var->s_w * ((int)var->s_h - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

void drawbmp (char * filename) {

unsigned int headers[13];
FILE * outfile;
int extrabytes;
int paddedsize;
int x; int y; int n;
int red, green, blue;
int WIDTH = 600;
int HEIGHT = 800;

extrabytes = 4 - ((WIDTH * 3) % 4);                 // How many bytes of padding to add to each
                                                    // horizontal line - the size of which must
                                                    // be a multiple of 4 bytes.
if (extrabytes == 4)
   extrabytes = 0;

paddedsize = ((WIDTH * 3) + extrabytes) * HEIGHT;

// Headers...
// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

headers[0]  = paddedsize + 54;      // bfSize (whole file size)
headers[1]  = 0;                    // bfReserved (both)
headers[2]  = 54;                   // bfOffbits
headers[3]  = 40;                   // biSize
headers[4]  = WIDTH;  // biWidth
headers[5]  = HEIGHT; // biHeight

// Would have biPlanes and biBitCount in position 6, but they're shorts.
// It's easier to write them out separately (see below) than pretend
// they're a single int, especially with endian issues...

headers[7]  = 0;                    // biCompression
headers[8]  = paddedsize;           // biSizeImage
headers[9]  = 0;                    // biXPelsPerMeter
headers[10] = 0;                    // biYPelsPerMeter
headers[11] = 0;                    // biClrUsed
headers[12] = 0;                    // biClrImportant

outfile = fopen(filename, "wb");

//
// Headers begin...
// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
//

fprintf(outfile, "BM");

for (n = 0; n <= 5; n++)
{
   fprintf(outfile, "%c", headers[n] & 0x000000FF);
   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
}

// These next 4 characters are for the biPlanes and biBitCount fields.

fprintf(outfile, "%c", 1);
fprintf(outfile, "%c", 0);
fprintf(outfile, "%c", 24);
fprintf(outfile, "%c", 0);

for (n = 7; n <= 12; n++)
{
   fprintf(outfile, "%c", headers[n] & 0x000000FF);
   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
}

//
// Headers done, now write the data...
//

for (y = HEIGHT - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
{
   for (x = 0; x <= WIDTH - 1; x++)
   {

    //   red = reduce(redcount[x][y] + COLOUR_OFFSET) * red_multiplier;
    //   green = reduce(greencount[x][y] + COLOUR_OFFSET) * green_multiplier;
    //   blue = reduce(bluecount[x][y] + COLOUR_OFFSET) * blue_multiplier;
	red = 0;
	green = 0;
	blue = 255;

      if (red > 255) red = 255; if (red < 0) red = 0;
      if (green > 255) green = 255; if (green < 0) green = 0;
      if (blue > 255) blue = 255; if (blue < 0) blue = 0;

      // Also, it's written in (b,g,r) format...

      fprintf(outfile, "%c", blue);
      fprintf(outfile, "%c", green);
      fprintf(outfile, "%c", red);
   }
   if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
   {
      for (n = 1; n <= extrabytes; n++)
      {
         fprintf(outfile, "%c", 0);
      }
   }
}

fclose(outfile);
return;
}

int	screenshot(var_t *var)
{
	drawbmp("test.bmp");	
	exit(0);
	return (1);
}

int		run(var_t *var)
{
	int t_endian;
	int t_bpp;
	int t_line;
	int i = 0;

	var->tex_h = 64;
	var->tex_w = 64;
	var->img_data = (int *)mlx_get_data_addr(var->img, &var->t_bpp, &var->t_line, &var->t_endian);
	listen_keys(var);
	if (var->S || var->W || var->D || var->A
	|| var->R_R || var->L_R)
		cls(var);
	raycast(var);
	//sortQueue(var);
	while (i < var->spriteNum)
	{
		var->dist = getDist(var);
		//printf("%f |%f| |%f|, ", var->dist[i], var->posX, var->posY);
		draw_sprite(var, var->spriteQueue[var->spriteorder[i]][0], var->spriteQueue[var->spriteorder[i]][1]);
		i++;
	}
	if (var->screenshot)
		screenshot(var);	
	//draw_sprite(var);
	mlx_put_image_to_window(var->mlx_ptr, var->mlx_win, var->img, 0, 0);
}

int		start(var_t *var)
{
	load_text(var);
	mlx_loop_hook(var->mlx_ptr, run, (void *)var);
	mlx_loop(var->mlx_ptr);
}

int	**copyMap(int height, int width, int index, var_t *var)
{
	int **map;
	char **str;
	char *tmp;
	int i;
	int y;

	i = 0;
	y = 0;
	map = malloc(sizeof(int *) * height);
	str = ft_split(&var->paramFile[index], '\n');
	while (i < height)
  {
    map[i] = malloc(sizeof(int) * width);
    i++;
  }
	i = 0;
		while (str[i])
		{
			while (ft_split(str[i], ' ')[y])
			{
				map[i][y] = (ft_split(str[i], ' '))[y][0] - 0;
				y++;
			}
			y = 0;
			i++;			
		}
	return (map);
}

int	spaceCount(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void	checkLine(char *str, int y)
{
	int i;

	i = 0;
	while (str[i] && i <= y)
	{
		if (str[i] == ' ')
			i++;
		if (!isWall(str[i]))
			{
				ft_printf("MAP_NOT_CLOSED");
				exit (0);
			}
		i++;
	}
}

int *init_to_fill(var_t *var)
{
	int *to_fill;
	int i;

	i = 0;
	if (!(to_fill = malloc(sizeof(int) * var->m_width)))
		return (0);
	while (i < var->m_width)
	{
		to_fill[i] = -1;
		i++;
	}
	return (to_fill);
}

int getMapHeight(char **str)
{
	int height;
	int i;
	int y;

	i = 0;
	y = 0;
	height = 0;
	while (str[i])
	{
		if (i > 0 && spaceCount(str[i]) < spaceCount(str[i - 1]))
			checkLine(str[i], spaceCount(str[i - 1]));
		if (str[i][0] == ' ')
		{
			y = 0;
			while (str[i][y] == ' ')
				y++;
			if (!isWall(str[i][y]))
				{
					ft_printf("MAP_NOT_CLOSED");
					exit(0);
				}
		}
		else
			y = 0;
		i++;
	}
	return (i);
}

int	getMapWidth(char **str)
{
	int width;
	int i;
	int big;
	int index;

	i = 0;
	width = 0;
	big = ft_strlen(str[i]);
	index = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > big)
		{
			big = ft_strlen(str[i]);
			index = i;
		}			
		i++;
	}
	i = 0;
	while (str[index][i])
	{
		if (!(str[index][i] == ' '))
			width++;
		i++;
	}
return (width + (spaceCount(str[index]) / 2));
}

void	initSpriteQueue(var_t *var)
{
	int i = 0;
	int y = 0;
	int z = 0;

	var->spriteQueue = malloc(sizeof(int *) * var->spriteNum);
	while (i < var->spriteNum)
	{
		var->spriteQueue[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (y < var->m_height)
  	{
    while (i < var->m_width)
  	{
		if (var->map[y][i] == 6)
		{
			var->map[y][i] = 0;
			var->spriteX = y;
			var->spriteY = i;
			var->spriteQueue[z][0] = y;
			var->spriteQueue[z][1] = i;
			//ft_printf("\nsprite -->%d %d", var->spriteX, var->spriteQueue[0][0]);
			z++;
		}
    	i++;
  	}
  i = 0;
  y++;
  }

}

void duplicate_map(var_t *var, char **str2)
{
	char **str;
	char c;
	int i;
	int y;
	
	i = 0;
	y = 0;
	var->map = malloc(sizeof(int *) * var->m_height);
	var->spriteNum = 0;
	while (i < var->m_height)
  	{
    var->map[i] = malloc(sizeof(int) * var->m_width);
    i++;
  	}
  i = 0;
  while (y < var->m_height)
  {
    while (i < var->m_width)
  	{
		 str = ft_split(str2[y], ' ');
		 var->map[y][i] = str[i][0] - '0';
		 if (var->map[y][i] == 6)
			var->spriteNum++;
		if (var->map[y][i] == 4)
		{
			var->posX = y + 1;
			var->posY = i + 1;
		}
    i++;
  	}
  i = 0;
  y++;
  }
}

int	skip(char ***split)
{
	char *str = **split;
	if (str[0] == 'R' || str[0] == 'F'
	|| str[0] == 'C' || str[0] == 'S')
		return (1);
	if ((str[0] == 'S' && str[1] == 'O')
	|| (str[0] == 'N' && str[1] == 'O')
	|| (str[0] == 'W' && str[1] == 'E')
	|| (str[0] == 'E' && str[1] == 'A'))
		return (1);
	return (0);
}

char	**getMapStr(var_t *var)
{
	int width;
	char *str;
	char **split;
	char *ptr;
	int i;
	int z;

	str = ft_strdup(var->paramFile);
	split = ft_split(str, '\n');
	width = 0;
	z = 0;
	ptr = *split;
	while (skip(&split))
	{
		free(*split);
		split++;
	}
		
	return (split);
}

void checkBottom(char *str)
{
	int i;
	int y;
	int count;

	i = 0;
	y = 0;
	count = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!isWall(str[i]))
			{
				ft_printf("MAP_NOT_CLOSED");
				exit(0);
			}
		i++;
	}
}

void checkTop(char *str)
{
	int i;
	int y;
	int count;

	i = 0;
	y = 0;
	count = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!isWall(str[i]))
			{
				ft_printf("MAP_NOT_CLOSED");
				exit (0);
			}
		i++;
	}
}

int isSymbol(char c)
{
	if (c == '4')
		return (1);
	else if (c == '5')
		return (1);
	else if (c == '6')
		return (1);
	else if (c == '2')
		return (1);
	else if (c == '1')
		return (1);
	else if (c == '3')
		return (1);
	else if (c == '0')
		return (1);
	return (0);
}

void	lineIsOk(char *str)
{
	int i;
	
	i = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	if (!isWall(str[i]))
	{
		ft_printf("MAP_NOT_CLOSED");
		exit(0);
	}	
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!isSymbol(str[i]))
			{
				ft_printf("%c MAP_SYMBOL_UNKOWN", str[i]);
				exit(0);
			}
		i++;
	}
	if (!isWall(str[i - 1]))
	{
		printf("MAP_NOT_CLOSED");
		exit(0);
	}
}

void checkMiddle(char **str)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (str[i + 1])
	{
		lineIsOk(str[i]);
		i++;
	}
}

void checkMap(char **str)
{
	int i;

	i = 0;
	checkTop(str[0]);
	checkMiddle(str);
	while (str[i])
		i++;
	checkBottom(str[i - 1]);
}

char *rmSpace(char *str)
{
	char *ret;
	int newsize;
	int i;
	int y;

	newsize = ft_strlen(str) * 2;
	ret = malloc(sizeof(char) *  newsize);
	i = 0;
	y = 0;
	while (y < newsize - 1)
	{
		if (y % 2 == 0)
		{
			ret[y] = str[i] == ' ' ? '1' : str[i];
			i++;
		}
		else
			ret[y] = ' ';
		y++;
	}
	ret[newsize - 1] = '\0';
	return (ret);
}

char *NoRestrict_removeS(char *str)
{
	int i = 0;

	while (str[i])
	{
			if (str[i] == 'S')
				str[i] = '3';
			else if (str[i] == 'N')
				str[i] = '2';
			else if (str[i] == 'W')
				str[i] = '4';
			else if (str[i] == '2')
				str[i] = '6';
			else if (str[i] == 'E')
				str[i] = '5';	
		i++;
	}
	return (str);
}

int	containSpace(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (isWall(str[i]) && isWall(str[i + 1]) && isWall(str[i + 2]))
		return (1);
	return (0);
}

char	**convMap(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = rmSpace(str[i]);
		str[i] = NoRestrict_removeS(str[i]);
		ft_printf("%s\n", str[i]);
		i++;
	}
	return (str);
}

char **convSpace(char **str)
{
	int i;
	int y;
	int z;

	i = 0;
	y = 0;
	z = 0;
	while (str[i])
	{
		z = spaceCount(str[i]);
		while (z > 0 && y < z)
		{
			if (y % 2 == 0)
				str[i][y] = '1';
			y++;
		}
		y = 0;
		i++;
	}
	return (str);
}

void getMapFromParamFile(var_t *var)
{
	int i;
	int index;
	char **str;
	int newsize;

	str = getMapStr(var);
	index = getMapIndex(var);
	i = 0;
	if (containSpace(str[0]))
		str = convMap(str);
	//exit(0);
	checkMap(str);
	var->m_width = getMapWidth(str);
	ft_printf("width = %d\n", var->m_width);
	var->m_height = getMapHeight(str);
	str = convSpace(str);
		while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	printf("-->%d", var->m_width);
	//exit(0);
	duplicate_map(var, str);
	if (var->posX == -1 || var->posY == -1)
		{
			ft_printf("NO_PLAYER_START");
			exit(0);
		}
	initSpriteQueue(var);
}

void	checkColor(var_t *var)
{
	int i = 0;
	while (i < 3)
	{
		if (!(var->F_color[i] > -1 && var->F_color[i] < 256))
			{
				ft_printf("COLOR_ERROR");
				exit (0);
			}
			i++;
	}
	i = 0;
	while (i < 3)
	{
		if (!(var->C_color[i] > -1 && var->C_color[i] < 256))
			{
				ft_printf("COLOR_ERROR");
				exit (0);
			}
			i++;
	}
}

void	init_struct(var_t *var, char **argv)
{
	int fd;
    char *line;
    int i = 0;
    int y = 0;

	var->posX = -1;
	var->posY = -1;
    var->paramFile = NULL;
	var->ParamSliced = NULL;
	var->screenshot = 0;
	if (ft_strcmp(argv[1], "--save"))
		var->screenshot = 1;
    fd = open(argv[var->screenshot == 1 ? 2 : 1], O_RDONLY);
    getParamFile(fd, &line, var);
	getMapFromParamFile(var);
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
	checkColor(var);
}

int	main(int argc, char **argv)
{
	var_t var;

	if (!(argc >= 2 && argc <= 3))
	{
		ft_printf("Please use [--save] argument to save the first frame into a bmp file\nfollowed by a .cub map or directly the map to launch the game");
		exit(0);
	}
	init_struct(&var, argv);
	if ((var.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((var.mlx_win = mlx_new_window(var.mlx_ptr, var.s_w, var.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	init_raycast(&var);
	init_keys(&var, 5);
	start(&var);
	return (EXIT_SUCCESS);
}