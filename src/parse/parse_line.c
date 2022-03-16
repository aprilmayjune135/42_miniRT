/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 10:28:35 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 19:07:17 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_line(char *s, t_scene *scene)
{
	int		pos;
	int		obj_shape;

	pos = 0;
	while (ft_isspace(s[pos]))
		pos++;
	if (!s[pos])
		return (1);
	obj_shape = get_obj_shape(s + pos);
	if (obj_shape == -3)
		return (parse_filter(s, &(scene->color_filter)));
	if (obj_shape == -2)
		return (parse_resolut(s, &(scene->image_size)));
	if (obj_shape == -1)
		return (parse_ambient(s, &(scene->ambient_light)));
	if (obj_shape == 0)
		return (parse_obj(s, &(scene->cameras), obj_shape));
	if (obj_shape == 1 || obj_shape == 2)
		return (parse_obj(s, &(scene->lights), obj_shape));
	if (obj_shape > 2)
		return (parse_obj(s, &(scene->objs), obj_shape));
	return (return_error(-1, "Unrecognized input!\n"));
}

int	check_normal_input(t_vec3 normal)
{
	if (normal.x < -1 || normal.x > 1)
		return (-1);
	if (normal.y < -1 || normal.y > 1)
		return (-1);
	if (normal.z < -1 || normal.z > 1)
		return (-1);
	if (fabs(normal.x) < 1e-8 && fabs(normal.y) < 1e-8 && fabs(normal.z) < 1e-8)
		return (-1);
	return (1);
}

int	parse_resolut(char *s, t_int2 *image_size)
{
	int			pos;
	static int	count;

	pos = 1;
	if (count > 0)
		return (return_error(-1, "Resolution declared more than once!\n"));
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, resolution is incorrect!\n"));
	if (read_int(s, &pos, &image_size->x) == -1 || image_size->x <= 0)
		return (return_error(-1, "Dear, your resolution is incorrect!\n"));
	if (read_int(s, &pos, &image_size->y) == -1 || image_size->y <= 0)
		return (return_error(-1, "Dear, resolution is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, resolution is incorrect!\n"));
	count++;
	return (1);
}

int	parse_ambient(char *s, t_vec3 *color)
{
	int			pos;
	double		ratio;
	static int	count;

	pos = 1;
	if (count > 0)
		return (return_error(-1, "Ambient light declared more than once!\n"));
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, ambient light input is incorrect!\n"));
	if (read_double(s, &pos, &ratio) == -1 || ratio < 0 || ratio > 1)
		return (return_error(-1, "Dear, ambient light ratio is incorrect!\n"));
	if (read_color(s, &pos, color) == -1)
		return (return_error(-1, "Dear, ambient light color is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, ambient light input is incorrect!\n"));
	count++;
	*color = v_multiply_t(ratio, *color);
	return (1);
}

int	parse_filter(char *s, int *color_filter)
{
	int			pos;
	static int	count;

	pos = 1;
	if (count > 0)
		return (return_error(-1, "Color filter declared more than once!\n"));
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, color filter input is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos] == 'R' || s[pos] == 'G' || s[pos] == 'B'
		|| s[pos] == 'W' || s[pos] == 'S')
	{
		*color_filter = (int)s[pos];
		pos++;
	}
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, color filter  input is incorrect!\n"));
	count++;
	return (1);
}
