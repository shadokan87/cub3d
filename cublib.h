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

	//sprite
	double vmove;
	double spritex;
	double spritey;
	double invdet;
	double transformx;
	double transformy;
	int vmovescreen;
	int spritescreenx;
	int spriteheight;
	int drawstarty;
	int drawendy;
	int spritewidth;
	int drawstartx;
	int drawendx;
	int texx;
	int texy;
	//sprite
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
	void *spriteVar;
}	var_t;

void	initcolormap(var_t *var);
void	inithextable(var_t *var);
void	checkColor(var_t *var);
void getMapFromParamFile(var_t *var);
char **convSpace(char **str);
char	**convMap(char **str);
int	containSpace(char *str);
char *NoRestrict_removeS(char *str);
char *rmSpace(char *str);
void checkMap(char **str, var_t *var);
void checkMiddle(char **str, var_t *var);
void	lineIsOk(char *str, var_t *var);
int isSymbol(char c);
int checkTop(char *str);
int checkBottom(char *str);
char	**getMapStr(var_t *var);
int	skip(char ***split);
void duplicate_map(var_t *var, char **str2);
void	initSpriteQueue(var_t *var);
int	getMapWidth(char **str);
int getMapHeight(char **str);
int *init_to_fill(var_t *var);
int	spaceCount(char *str);
int	**copyMap(int height, int width, int index, var_t *var);
int		start(var_t *var);
int		run(var_t *var);
void drawbmp (char *filename, var_t *var);
void	writeColor(var_t *var, int extrabytes, int fd);
void	writeHeader(int fd, unsigned int *headers);
unsigned int	*getHeader(int width, int height, int paddedsize);
int	load_text(var_t *var);
int	listen_keys(var_t *var);
int	movement(var_t *var);
void	l_r(var_t *var);
void	x_y(var_t *var);
void	fwd_bckwrd(var_t *var);
int	move_is_possible(int pos);
int		key_released(int keycode, var_t *var);
int		key_pressed(int keycode, var_t *var);
void	init_keys(var_t *var, int key_number);
void	raycast(var_t *var);
void	draw(var_t *var);
int	convHex(char *hex);
void	draw_texture(var_t *var);
void	draw_info(var_t *var);
void	cls(var_t *var);
void	hit(var_t *var);
void	draw_sprite(var_t *var, int sx, int sy);
void	init_sprite_var(var_t *var, int sx, int sy);
double	*getDist(var_t *var);
double	*sortqueue(var_t *var, double *dist);
int *cpy(var_t *var, int *tab);
void	step(var_t *var);
void	init_raycast(var_t *var);
int	verline(var_t *var, int x, int draw_start, int draw_end, int color);
void	pixel_put(var_t *var, int x, int y, int color);
void	pixel_put_fd(var_t *var, int color, int fd);
int	getgreen(int rgb, var_t *var);
int	getblue(int rgb, var_t *var);
int	getred(int rgb, var_t *var);
void   fillLoopParams(var_t *var);
void    fill_color(var_t *var, int i);
int  ft_strcmp(char *str, char *str2);
void    getParamFile(int fd, char **line, var_t *var);
char *removeS(char *str, var_t *var);
int	NoSpaceGetMapIndex(char *str);
int     ft_tolower(int c);
int	getMapIndex(var_t *var);
int	isWall(char c);
char *Remove_extraSpaces(char *str);
int		rgb_int(int red, int green, int blue);
void    *ft_memset(void *b, int c, size_t len);
void	closeGame(var_t *var, char *message);

































#endif
