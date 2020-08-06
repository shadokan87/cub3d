#include "cublib.h"

void	closeGame(var_t *var, char *message)
{
	int i;

	i = -1;
	if (var->mlx_ptr)
		free(var->mlx_ptr);
	if (var->mlx_win)
		free(var->mlx_win);
	if (var->addr)
		free(var->addr);
	while (++i < var->spriteNum && var->spriteQueue)
		var->spriteQueue[i] ? free(var->spriteQueue[i]) : 0;
	message ? ft_fprintf(1, message) : 0;
	exit(0);
}

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

    ret = 0;
	i = 0;
    while ((ret = get_next_line(fd, line)) > 0)
	{	
			*line = removeS(*line, var);
		var->paramFile = ft_strjoin(var->paramFile ? var->paramFile : "", *line);
		*line ? free(*line) : 0;
	}
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

int	getred(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, HEXD);
	if (rgb == 0)
		return (0);
	str[0] = hex[0];
	str[1] = hex[1];
	str[2] = '\0';
	if (str[0] == '0' && str[1] == '0')
		str[1] = '\0';
	while (i < 255)
	{
		if (ft_strcmp(var->hextable[i], str))
			return (i);
			
		i++;
	}
	return (255);
}

int	getblue(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, HEXD);
	if (rgb == 0)
		return (0);
	str[0] = hex[4];
	str[1] = hex[5];
	str[2] = '\0';
	if (str[0] == '0' && str[1] == '0')
		str[1] = '\0';
	while (i < 255)
	{
		if (ft_strcmp(var->hextable[i], str))
			return (i);
		i++;
	}
	return (255);
}

int	getgreen(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, HEXD);
	if (rgb == 0)
		return (0);
	str[0] = hex[2];
	str[1] = hex[3];
	str[2] = '\0';
	if (str[0] == '0' && str[1] == '0')
		str[1] = '\0';
	while (i < 255)
	{
		if (ft_strcmp(var->hextable[i], str))
			return (i);
		i++;
	}
	return (255);
}

void	pixel_put_fd(var_t *var, int color, int fd)
{
	int blue;
	int green;
	int red;

	red = getred(color, var);
	blue = getblue(color, var);
	green = getgreen(color, var);
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
    if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	ft_fprintf(fd, "%c", blue);
	ft_fprintf(fd, "%c", green);
	ft_fprintf(fd, "%c", red);
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

int *cpy(var_t *var, int *tab)
{
	int *ret = malloc(sizeof(int) * 2);
	ret[0] = tab[0];
	ret[1] = tab[1];
	return (ret);
}

double	*sortqueue(var_t *var, double *dist)
{
	int i;
	double swap;
	double swap2;

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
	return (sortqueue(var, dist));
}

void	init_sprite_var(var_t *var, int sx, int sy)
{
	var->vmove = 0.5;
	var->spritex = sx - var->posX;
	var->spritey = sy - var->posY;
	var->invdet = 1.0 / (var->planeX * var->dirY - var->dirX * var->planeY);
	var->transformx = var->invdet * (var->dirY * var->spritex - var->dirX * var->spritey);
	var->transformy = var->invdet * (-var->planeY * var->spritex + var->planeX * var->spritey);
	var->vmovescreen = (int)(var->vmove / var->transformy);
	var->spritescreenx = (int)((var->s_w / 2 * (1 + var->transformx / var->transformy)));
	var->spriteheight = abs((int)(var->s_h / (var->transformy)));
	var->drawstarty = -var->spriteheight / 2 + var->s_h / 2 + var->vmovescreen;
	if (var->drawstarty < 0)
		var->drawstarty = 0;
	var->drawendy = var->spriteheight / 2 + var->s_h / 2 + var->vmovescreen;
	if (var->drawendy >= var->s_h)
		var->drawendy = var->s_h - 1;
	var->spritewidth = abs((int)(var->s_h / (var->transformy)));
	var->drawstartx = -var->spritewidth / 2 + var->spritescreenx;
	if (var->drawstartx < 0)
		var->drawstartx = 0;
	var->drawendx = var->spritewidth / 2 + var->spritescreenx;
	if (var->drawendx >= var->s_w)
		var->drawendx = var->s_w - 1;
}

void	draw_sprite(var_t *var, int sx, int sy)
{
		int x;
		int y;
		int color;
		int d;

	init_sprite_var(var, sx, sy);
	x = var->drawstartx - 1;
	while (++x < var->drawendx)
	{
		if (var->transformy > 0 && x > 0 && x < var->s_w && var->transformy < var->zBuffer[x])
		{
			y = var->drawstarty - 1;
			var->texx = (int)(256 * (x - (-var->spritewidth / 2 + var->spritescreenx)) * var->tex_w/ var->spritewidth) / 256;

			while(++y < var->drawendy)
			{
				d = (y - var->vmovescreen) * 256 - var->s_h * 128 + var->spriteheight * 128;
				var->texy = ((d * var->tex_h / var->spriteheight) / 256);
				color = var->loaded_addr[6][(var->texx + var->texy * var->tex_w)];
				if ((color & 0x00FFFFFF) != 0) pixel_put(var, x, y, color);
			}
		}
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
		pixel_put(var, var->x, var->drawStart, var->loaded_addr[var->hit][64 * texy + texx]);
		var->drawStart++;
	}

}

int	convHex(char *hex)
{
	int i;

	i = 0;
	while (!(ft_strcmp(hex, ft_putnbr_base(i, HEXD))))
		{
			if (i > 255)
			{
				return (255);
			}
			i++;
		}
	return (i);
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
		closeGame(var, "ESC_PRESSED");
	else if (keycode == 13)
		var->W = 1;
	else if (keycode == 0)
		var->A = 1;
	else if (keycode == 1)
		var->S = 1;
	else if (keycode == 2)
		var->D = 1;
	else if (keycode == 123)
		var->L_R = 1;
	else if (keycode == 124)
		var->R_R = 1;
	return (0);	
}

int		key_released(int keycode, var_t *var)
{
	if (keycode == 53)
		var->ESC = 0;
	else if (keycode == 13)
		var->W = 0;
	else if (keycode == 0)
		var->A = 0;
	else if (keycode == 1)
		var->S = 0;
	else if (keycode == 2)
		var->D = 0;
	else if (keycode == 123)
		var->L_R = 0;
	else if (keycode == 124)
		var->R_R = 0;
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
			ft_fprintf(1, "---->%s |%d|\n", var->text_paths[i],i);
			var->loaded_text[i] = mlx_xpm_file_to_image(var->mlx_ptr, var->text_paths[i], &var->tex_w, &var->tex_h);
			var->loaded_addr[i] = (int *)mlx_get_data_addr(var->loaded_text[i], &t_bpp, &t_line, &t_endian);
		}
		else
		ft_fprintf(1, "ERR: --> %d\n", i);
		i++;
	}
}

unsigned int	*getHeader(int width, int height, int paddedsize)
{
	unsigned int *headers;

	if (!(headers = malloc(sizeof(unsigned int) * 13)))
		return (0);
	headers[0]  = paddedsize + 54;     
	headers[1]  = 0;                   
	headers[2]  = 54;                  
	headers[3]  = 40;             
	headers[4]  = width;
	headers[5]  = height;
	headers[7]  = 0;               
	headers[8]  = paddedsize;           
	headers[9]  = 0;                   
	headers[10] = 0;                    
	headers[11] = 0;                    
	headers[12] = 0;
	return (headers);
}

void	writeHeader(int fd, unsigned int *headers)
{
	int i;

	i = -1;
	while (++i <= 5)
	{
		ft_fprintf(fd, "%c", headers[i] & 0x000000FF);
		ft_fprintf(fd, "%c", (headers[i] & 0x0000FF00) >> 8);
		ft_fprintf(fd, "%c", (headers[i] & 0x00FF0000) >> 16);
		ft_fprintf(fd, "%c", (headers[i] & (unsigned int) 0xFF000000) >> 24);
	}
	ft_fprintf(fd, "%c", 1);
	ft_fprintf(fd, "%c", 0);
	ft_fprintf(fd, "%c", 24);
	ft_fprintf(fd, "%c", 0);
	i = 6;
	while (++i <= 12)
	{
		ft_fprintf(fd, "%c", headers[i] & 0x000000FF);
		ft_fprintf(fd, "%c", (headers[i] & 0x0000FF00) >> 8);
		ft_fprintf(fd, "%c", (headers[i] & 0x00FF0000) >> 16);
		ft_fprintf(fd, "%c", (headers[i] & (unsigned int) 0xFF000000) >> 24);
	}
}

void	writeColor(var_t *var, int extrabytes, int fd)
{
	int y;
	int x;
	char *dst;
	int color;
	int i;

	y = var->s_h;
	while (--y >= 0)
	{
	x = -1;
   while(++x <= var->s_w - 1)
   {
	dst =  var->addr + (y * var->line + x * (var->bpp / 8));;
	color = *(unsigned int*)dst;
	pixel_put_fd(var, color, fd);
   }
   if (extrabytes)
   {
      for (i = 1; i <= extrabytes; i++)
      {
         ft_fprintf(fd, "%c", 0);
      }
   }
}
}

void drawbmp (char *filename, var_t *var)
{
unsigned int *headers;
int extrabytes;
int paddedsize;
int fd;

fd = open(filename, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT);
extrabytes = 4 - ((var->s_w * 3) % 4) % 4;                 
if (extrabytes == 4)
   extrabytes = 0;
paddedsize = ((var->s_w * 3) + extrabytes) * var->s_h;
headers = getHeader(var->s_w, var->s_h, paddedsize);                  
ft_fprintf(fd, "BM");
writeHeader(fd, headers);
writeColor(var, extrabytes, fd);
close(fd);
closeGame(var, "--save done");
return;
}

int	screenshot(var_t *var)
{
	int i;

	i = 0;
	raycast(var);
	while (i < var->spriteNum)
	{
		var->dist = getDist(var);
		draw_sprite(var, var->spriteQueue[var->spriteorder[i]][0], var->spriteQueue[var->spriteorder[i]][1]);
		i++;
	}	
	drawbmp("screenshot2.bmp",var);
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
	if (var->screenshot)
		screenshot(var);
	listen_keys(var);
	if (var->S || var->W || var->D || var->A
	|| var->R_R || var->L_R)
		cls(var);
	raycast(var);
	while (i < var->spriteNum)
	{
		var->dist = getDist(var);
		draw_sprite(var, var->spriteQueue[var->spriteorder[i]][0], var->spriteQueue[var->spriteorder[i]][1]);
		i++;
	}	
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

int	checkLine(char *str, int y)
{
	int i;

	i = 0;
	while (str[i] && i <= y)
	{
		if (str[i] == ' ')
			i++;
		if (!isWall(str[i]))
			return (0);
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
			if (!(checkLine(str[i], spaceCount(str[i - 1]))))
				return (0);
		if (str[i][0] == ' ')
		{
			y = 0;
			while (str[i][y] == ' ')
				y++;
			if (!isWall(str[i][y]))
				return (0);
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
			var->posX = y + 1.5;
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

int checkBottom(char *str)
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
			return (0);
		i++;
	}
	return (1);
}

int checkTop(char *str)
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
				return (0);
		i++;
	}
	return (1);
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

void	lineIsOk(char *str, var_t *var)
{
	int i;
	
	i = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	if (!isWall(str[i]))
		closeGame(var, "MAP_NOT_CLOSED");	
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!isSymbol(str[i]))
			closeGame(var,"MAP_SYMBOL_UNKNOWN");
		i++;
	}
	if (!isWall(str[i - 1]))
		closeGame(var, "MAP_NOT_CLOSED");
}

void checkMiddle(char **str, var_t *var)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (str[i + 1])
	{
		lineIsOk(str[i], var);
		i++;
	}
}

void checkMap(char **str, var_t *var)
{
	int i;

	i = 0;
	if (!checkTop(str[0]))
		closeGame(var, "MAP_NOT_CLOSED");
	checkMiddle(str, var);
	while (str[i])
		i++;
	if (!(checkBottom(str[i - 1])))
		closeGame(var, "MAP_NOT_CLOSED");
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
		ft_fprintf(1, "%s\n", str[i]);
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
	checkMap(str, var);
	var->m_width = getMapWidth(str);
	ft_fprintf(1, "width = %d\n", var->m_width);
	if (!(var->m_height = getMapHeight(str)))
		closeGame(var, "MAP_NOT_CLOSED");
	str = convSpace(str);
		while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	duplicate_map(var, str);
	if (var->posX == -1 || var->posY == -1)
		closeGame(var, "NO_PLAYER_START");
	initSpriteQueue(var);
}

void	checkColor(var_t *var)
{
	int i = 0;
	while (i < 3)
	{
		if (!(var->F_color[i] > -1 && var->F_color[i] < 256))
			closeGame(var, "COLOR_ERROR");
			i++;
	}
	i = 0;
	while (i < 3)
	{
		if (!(var->C_color[i] > -1 && var->C_color[i] < 256))
			closeGame(var, "COLOR_ERROR");
			i++;
	}
}

void	inithextable(var_t *var)
{
	int i;

	i = 0;
	while (i <= 255)
	{
		var->hextable[i] = ft_putnbr_base(i, HEXD);
		i++;
	}
}

void	initcolormap(var_t *var)
{
	int i;

	i = 0;
	var->colormap = malloc(sizeof(int *) * var->m_height);
	while (i < var->m_height)
  	{
    var->colormap[i] = malloc(sizeof(int) * var->m_width);
    i++;
  	}
}

void	init_struct(var_t *var, char **argv)
{
	int fd;
    char *line;
    int i;

	i = -1;
	inithextable(var);
	var->posX = -1;
	var->posY = -1;
    var->paramFile = NULL;
	var->ParamSliced = NULL;
	var->screenshot = 0;
	var->mlx_win = NULL;
	var->mlx_ptr = NULL;
	var->addr = NULL;
	if (ft_strcmp(argv[1], "--save"))
		var->screenshot = 1;
    fd = open(argv[var->screenshot == 1 ? 2 : 1], O_RDONLY);
    getParamFile(fd, &line, var);
	getMapFromParamFile(var);
	initcolormap(var);
    while (var->paramFile[++i])
		var->paramFile[i] == '\n' ? (var->paramFile[i] = ' ') : 0;
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
		ft_fprintf(1, "Please use [--save] argument to save the first frame into a bmp file\nfollowed by a .cub file or directly the .cub file to launch the game");
		exit(0);
	}
	init_struct(&var, argv);
	if ((var.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if (var.s_w > 1914)
		var.s_w = 1914;
	if (var.s_h > 924)
		var.s_h = 924;
	if ((var.mlx_win = mlx_new_window(var.mlx_ptr, var.s_w, var.s_h, "cub3d")) == NULL)
	return (EXIT_FAILURE);
	init_raycast(&var);
	init_keys(&var, 5);
	start(&var);
	return (EXIT_SUCCESS);
}
