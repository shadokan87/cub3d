#include "cublib.h"

void	initspritequeue(var_t *var)
{
	int i = 0;
	int y = 0;
	int z = 0;

	var->spritequeue = malloc(sizeof(int *) * var->spritenum);
	while (i < var->spritenum)
	{
		var->spritequeue[i] = malloc(sizeof(int) * 2);
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
			var->spritex = y;
			var->spritey = i;
			var->spritequeue[z][0] = y;
			var->spritequeue[z][1] = i;
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
	var->spritenum = 0;
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
			var->spritenum++;
		if (var->map[y][i] == 4)
		{
			var->posx = y + 1.5;
			var->posy = i + 1;
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
	if (str[0] == 'r' || str[0] == 'f'
	|| str[0] == 'c' || str[0] == 's')
		return (1);
	if ((str[0] == 's' && str[1] == 'o')
	|| (str[0] == 'n' && str[1] == 'o')
	|| (str[0] == 'w' && str[1] == 'e')
	|| (str[0] == 'e' && str[1] == 'a'))
		return (1);
	return (0);
}

char	**getmapstr(var_t *var)
{
	int width;
	char *str;
	char **split;
	char *ptr;
	int i;
	int z;

	str = ft_strdup(var->paramfile);
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

int checkbottom(char *str)
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
		if (!iswall(str[i]))
			return (0);
		i++;
	}
	return (1);
}