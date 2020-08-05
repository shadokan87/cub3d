#ifndef CUBLIB_H
# define CUBLIB_H

# include <string.h>

# include <unistd.h>
# include <stdlib.h>
# include "gnl_working/get_next_line.h"
# include "ft_fprintf/lprintf.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdint.h>

# define rotSpeed 0.1
# define moveSpeed 0.1

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
	char *hextable[255];
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
	int **colormap;
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
	char **text_paths;
	int **loaded_text;
	int **loaded_addr;
    char *paramFile;
    int F_color[3];
    int C_color[3];
    char **ParamSliced;
	double zBuffer[10000];
	int y;
	int spriteNum;
	int *sX;
	int *sY;
	double spriteX;
	double spriteY;
	int *spriteorder;
	char	*addr;
	void	*mlx_ptr;
    void	*mlx_win;
	int **map;
	int	o_drawStart;
	int o_drawEnd;
	int o_x;
}	var_t;

#endif
