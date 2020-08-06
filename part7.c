#include "cublib.h"

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