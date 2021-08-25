#ifndef FILES_H
# define FILES_H
int		get_file_size(char	*file_name);
char	*dict_reader(char	*file_name, int	file_size);
int		get_line_number(char	*full_text);
char	**paragraph_split(char	*full_text, int	start, int	end);
#endif