#include <unistd.h>
#include <stdio.h>
#include "functions.h"
int	ft_str_is_printable(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if ((str[idx] < 32 || str[idx] > 126) && str[idx] != '\n')
			return (0);
		idx++;
	}
	return (1);
}

int	smallest_num(int	a, int	b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_strcmp(char s1, char s2)
{
	if (s1 == s2)
		return (0);
	return (1);
}

int	mid_loop(char **map, int	line, int	col, int	aux_range)
{	
	int	temp_line;
	int	temp_col;
	int	found;

	found = 0;
	temp_line = line;
	while (temp_line <= line + aux_range)
	{
		temp_col = col;
		while (temp_col <= col + aux_range)
		{
			if (ft_strcmp(map[temp_line][temp_col], map[0][2]) == 0)
			{
				found = 1;
			}
			temp_col++;
		}	
		temp_line++;
	}
	return (found);
}

int	biggest_square(char **map, int	*coord_init, int	max_line, int	max_col)
{
	int	max_range;
	int	aux_range;

	aux_range = 0;
	max_range = smallest_num(max_line - coord_init[0], max_col - coord_init[1]);
	while (aux_range < max_range)
	{
		if (mid_loop(map, coord_init[0], coord_init[1], aux_range) == 1)
			return (aux_range);
		aux_range++;
	}
	return (aux_range - 1);
}
