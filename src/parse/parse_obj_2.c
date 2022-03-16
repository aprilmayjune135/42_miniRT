/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 20:23:27 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 20:04:27 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tr	create_tr(t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	t_tr	new;

	new.a = p1;
	new.b = p2;
	new.c = p3;
	new.ab = v_minus(new.b, new.a);
	new.ac = v_minus(new.c, new.a);
	new.normal = v_unit_vector(v_cross(new.ab, new.ac));
	return (new);
}

int	parse_tr(char *s, t_obj *obj)
{
	int			pos;
	t_tr		new;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, triangle input is incorrect!\n"));
	if (read_vec3(s, &pos, &new.a) == -1
		|| read_vec3(s, &pos, &new.b) == -1
		|| read_vec3(s, &pos, &new.c) == -1)
		return (return_error(-1, "Dear, triangle point is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, triangle color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, triangle effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, triangle input is incorrect!\n"));
	obj->storage.tr[0] = create_tr(new.a, new.b, new.c);
	obj->normal = obj->storage.tr[0].normal;
	obj->center = v_multiply_t(1.0 / 3.0, v_add(new.a, v_add(new.b, new.c)));
	return (1);
}

int	parse_sq(char *s, t_obj *obj)
{
	int			pos;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, square input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, square center is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, square orient vector is incorrect!\n"));
	if (read_double(s, &pos, &obj->radius) == -1 || obj->radius < 0)
		return (return_error(-1, "Dear, square size is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, square color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, square effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, square input is incorrect!\n"));
	obj->normal = v_unit_vector(obj->normal);
	return (1);
}

int	parse_cy(char *s, t_obj *obj)
{
	int			pos;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, cy/co/pr input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, cy/co/pr center is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, cy/co/pr orient vector incorrect!\n"));
	if (read_double(s, &pos, &obj->radius) == -1 || obj->radius < 0)
		return (return_error(-1, "Dear, cy/co/pr diameter is incorrect!\n"));
	if (read_double(s, &pos, &obj->size_3d.y) == -1 || obj->size_3d.y < 0)
		return (return_error(-1, "Dear, cy/co/pr height is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, cy/co/pr color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, cy/co/pr effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, cy/co/pr input is incorrect!\n"));
	obj->normal = v_unit_vector(obj->normal);
	obj->storage.w_to_l = m_rotation(obj->normal, create_vec3(0, 0, 1));
	return (1);
}

int	parse_ds(char *s, t_obj *obj)
{
	int			pos;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, disc input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, disc center is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, disc orient vector is incorrect!\n"));
	if (read_double(s, &pos, &obj->radius) == -1 || obj->radius < 0)
		return (return_error(-1, "Dear, disc diameter is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, disc color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, disc effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, disc input is incorrect!\n"));
	obj->normal = v_unit_vector(obj->normal);
	return (1);
}
