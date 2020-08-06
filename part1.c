#include "cublib.h"

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