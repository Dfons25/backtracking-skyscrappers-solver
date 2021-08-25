#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "strs.h"
#include "files.h"
#include "map.h"
#include "functions.h"

void	fill_square(char **map, int	line, int col, int	max_range)
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

void	print_board(char **map)
{
	int	idx;

	idx = 1;
	while (map[idx])
	{
		ft_putstr(map[idx]);
		idx++;
	}
}

void	check_board(char **map, int	line, int col, int biggest)
{
	int	coord_init[2];
	int	temp_biggest;
	int	t_line;
	int	t_col;

	temp_biggest = 0;
	while (line++ < ft_catoi(map[0][0]))
	{
		col = -1;
		while (col++ < ft_strlen(map[1]))
		{
			coord_init[0] = line;
			coord_init[1] = col;
			temp_biggest = biggest_square(map, coord_init,
					ft_catoi(map[0][0]), ft_strlen(map[1]));
			if (biggest < temp_biggest)
			{
				biggest = temp_biggest;
				t_line = line;
				t_col = col;
			}
		}
	}
	fill_square(map, t_line, t_col, biggest);
}

void	ifelse(char **map)
{
	if (is_valid_map(map) == 0)
		ft_putstr("map error");
	else
	{
		check_board(map, 0, -1, 0);
		print_board(map);
	}
}

int	main(int argn, char	**argv)
{
	int		idx;
	char	*full_text;
	char	**map;

	idx = 1;
	if (argn > 1)
	{
		while (idx < argn)
		{
			full_text = dict_reader(argv[idx], get_file_size(argv[idx]));
			map = paragraph_split(full_text, 0, 0);
			ifelse(map);
			free(full_text);
			free(map);
			idx++;
			put_char('\n');
		}
	}
}
