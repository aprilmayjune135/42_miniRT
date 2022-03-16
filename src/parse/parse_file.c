/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:29:36 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 19:42:23 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	file_extension(char *file)
{
	size_t	len;

	if (!file)
		return (-1);
	len = ft_strlen(file);
	if (len > 3 && file[len - 1] == 't'
		&& file[len - 2] == 'r' && file[len - 3] == '.'
		&& file[len - 4] != 47)
		return (1);
	return (-1);
}

int	check_argument(int fd, int argc, char **argv, int *save_bmp)
{
	if (argc == 1)
		return (return_error(-1, "Dear, where is your scene file?\n"));
	else if (argc > 3)
		return (return_error(-1, "Dear, too many arguments!\n"));
	else if (file_extension(argv[1]) == -1)
		return (return_error(-1, "Dear, your file name should be *.rt!\n"));
	else if (fd == -1)
		return (return_error(-1, "Oops dear, errors in opening your file!\n"));
	else if (argc == 3 && (ft_strncmp(argv[2], "--save", 6)
			|| ft_strlen(argv[2]) > 6))
		return (return_error(-1, "Dear, second argument incorrect!\n"));
	*save_bmp = 0;
	if (argc == 3)
		*save_bmp = 1;
	return (argc);
}

void	init_scene(t_scene *scene)
{
	scene->image_size.x = -1;
	scene->ambient_light.x = -1;
	scene->color_filter = 0;
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->objs = NULL;
	scene->bump = NULL;
	scene->back_color = create_vec3(0, 0, 0);
}

int	parse_file(int fd, t_scene **scene)
{
	int		output;
	char	*line;

	*scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (return_error(-1, "Malloc error in scene!\n"));
	init_scene(*scene);
	output = 1;
	while (output == 1)
	{
		output = get_next_line(fd, &line);
		if (output == -1)
			return (return_error(-1, "Oops, reading file failed!\n"));
		if (parse_line(line, *scene) < 0)
			return (-1);
		free(line);
	}
	if ((*scene)->image_size.x < 0
		|| (*scene)->ambient_light.x < 0 || !(*scene)->cameras)
		return (return_error(-1, "rt file missing essention info!\n"));
	if (parse_bump((*scene)->objs, &((*scene)->bump)) == -1)
		return (return_error(-1, "failed to parse bump map (texture) file!\n"));
	return (1);
}
