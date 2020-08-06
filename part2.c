#include "cublib.h"

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