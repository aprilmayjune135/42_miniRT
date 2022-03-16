/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj_1.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 17:50:31 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 20:04:21 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(char *s, t_obj *obj)
{
	int			pos;

	pos = 1;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, camera input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, camera view point is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, camera orient vector is incorrect!\n"));
	if (read_double(s, &pos, &obj->radius) == -1
		|| obj->radius < 1e-8 || obj->radius > 180)
		return (return_error(-1, "Dear, camera FOV is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, camera input is incorrect!\n"));
	obj->normal = v_unit_vector(obj->normal);
	return (1);
}

int	parse_spot_light(char *s, t_obj *obj)
{
	int			pos;
	double		brightness;

	pos = 1;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, light input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, light point is incorrect!\n"));
	if (read_double(s, &pos, &brightness) == -1
		|| brightness < 0 || brightness > 1)
		return (return_error(-1, "Dear, light brightness is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, light color is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, light input is incorrect!\n"));
	obj->color = v_multiply_t(brightness, obj->color);
	return (1);
}

int	parse_dir_light(char *s, t_obj *obj)
{
	int			pos;
	double		brightness;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, light input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, light direction is incorrect!\n"));
	if (read_double(s, &pos, &brightness) == -1
		|| brightness < 0 || brightness > 1)
		return (return_error(-1, "Dear, light brightness is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, light color is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, light input is incorrect!\n"));
	obj->color = v_multiply_t(brightness, obj->color);
	obj->normal = v_unit_vector(obj->normal);
	return (1);
}

int	parse_sp(char *s, t_obj *obj)
{
	int			pos;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, sphere input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, sphere center is incorrect!\n"));
	if (read_double(s, &pos, &obj->radius) == -1 || obj->radius < 0)
		return (return_error(-1, "Dear, sphere diameter is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, sphere color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, sphere effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, sphere input is incorrect!\n"));
	return (1);
}

int	parse_pl(char *s, t_obj *obj)
{
	int			pos;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, plane input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, plane center is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, plane orient vector is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, plane color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, plane effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, plane input is incorrect!\n"));
	obj->normal = v_unit_vector(obj->normal);
	return (1);
}
