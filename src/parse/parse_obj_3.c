/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj_3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/13 19:27:59 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:29:39 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
**	cb = cube;
**	it follows the format:
**	center | normal | size_3d | color
*/

int	parse_cb(char *s, t_obj *obj)
{
	int			pos;

	pos = 2;
	if (!ft_isspace(s[pos]))
		return (return_error(-1, "Dear, cube input is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->center) == -1)
		return (return_error(-1, "Dear, cube center is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->normal) == -1
		|| check_normal_input(obj->normal) == -1)
		return (return_error(-1, "Dear, cube orient vector is incorrect!\n"));
	if (read_vec3(s, &pos, &obj->size_3d) == -1 || obj->size_3d.x < 1e-8
		|| obj->size_3d.y < 1e-8 || obj->size_3d.z < 1e-8)
		return (return_error(-1, "Dear, cube size is incorrect!\n"));
	if (read_color(s, &pos, &obj->color) == -1)
		return (return_error(-1, "Dear, cube color is incorrect!\n"));
	if (read_effect(s, &pos, &obj->effect) == -1)
		return (return_error(-1, "Dear, cube effect is incorrect!\n"));
	while (ft_isspace(s[pos]))
		pos++;
	if (s[pos])
		return (return_error(-1, "Dear, cube input is incorrect!\n"));
	obj->normal = v_unit_vector(obj->normal);
	return (1);
}
