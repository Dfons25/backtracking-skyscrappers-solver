#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "strs.h"
#include "files.h"
#include "map.h"
#include "functions.h"

void	fill_square(char **map, int	line, int	col, int	max_range)
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

int	main(int argn, char	**argv)
{
	char	*file_name;
	int		idx;
	char	*full_text;
	char	**map;
	int		coord_init[2];

	idx = 1;
	if (argn > 1)
	{
		while (idx < argn)
		{
			full_text = dict_reader(argv[idx], get_file_size(argv[idx]));
			map = paragraph_split(full_text, 0, 0);
			if (is_valid_map(map) == 0)
			{
				ft_putstr("map error");
			}
			else
			{
				coord_init[0] = 1;
				coord_init[1] = 2;
				check_board(map, coord_init);
				print_board(map);
			}
			free(full_text);
			free(map);
			idx++;
			put_char('\n');
		}
	}
}
