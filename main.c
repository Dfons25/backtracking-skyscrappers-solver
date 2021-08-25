#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "strs.h"
#include "files.h"
#include "map.h"

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

void fill_square(char **map, int	line, int	col, int	max_range)
{
	int	range;
	int	aux_range;

	range = 0;
	aux_range = 0;
	while (range < max_range)
	{
		aux_range = 0;
		while (aux_range < max_range)
		{
			map[line + range][col + aux_range] = map[0][3];
			aux_range++;
		}
		range++;
	}
}

void print_board(char **map)
{
	int	idx;

	idx = 1;
	while (map[idx])
	{
		ft_putstr(map[idx]);
		idx++;
	}
}

void	check_board(char **map, int	coord_init[2])
{
	int	*coord_sqr[2];
	int	biggest;
	int	temp_biggest;

	biggest = 0;
	temp_biggest = 0;
	while (coord_init[0] < ft_catoi(map[0][0]))
	{
		coord_init[1] = 0;
		while (coord_init[1] < ft_strlen(map[1]))
		{
			temp_biggest = biggest_square(map, coord_init,
					ft_catoi(map[0][0]), ft_strlen(map[1]));
			if (biggest < temp_biggest)
			{
				biggest = temp_biggest;
				coord_sqr[0] = (int) coord_init[0];
				coord_sqr[1] = (int) coord_init[1];
			}
			coord_init[1]++;
		}
		coord_init[0]++;
	}
	fill_square(map, coord_sqr[0], coord_sqr[1], biggest);
}

int	main(int	argn, char	**argv)
{
	char	*file_name;
	int idx;
	char	*full_text;
	char	**map;
	int	coord_init[2];

	idx = 1;
	if (argn > 1)
	{
		while (idx < argn)
		{
			full_text = dict_reader(argv[idx], get_file_size(argv[idx]));
			map = paragraph_split(full_text, 0, 0);
			if (is_valid_map(map) == 0)
				ft_putstr("map error");
			coord_init[0] = 1;
			coord_init[1] = 2;
			check_board(map, coord_init);
			print_board(map);
			free(full_text);
			free(map);
			idx++;
			put_char('\n');
		}
	}	
}
