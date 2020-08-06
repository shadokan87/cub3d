#include "cublib.h"

int	spacecount(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	checkline(char *str, int y)
{
	int i;

	i = 0;
	while (str[i] && i <= y)
	{
		if (str[i] == ' ')
			i++;
		if (!iswall(str[i]))
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

int getmapheight(char **str)
{
	int height;
	int i;
	int y;

	i = 0;
	y = 0;
	height = 0;
	while (str[i])
	{
		if (i > 0 && spacecount(str[i]) < spacecount(str[i - 1]))
			if (!(checkline(str[i], spacecount(str[i - 1]))))
				return (0);
		if (str[i][0] == ' ')
		{
			y = 0;
			while (str[i][y] == ' ')
				y++;
			if (!iswall(str[i][y]))
				return (0);
		}
		else
			y = 0;
		i++;
	}
	return (i);
}

int	getmapwidth(char **str)
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
return (width + (spacecount(str[index]) / 2));
}