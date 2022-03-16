/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   effect.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 11:17:52 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 18:03:44 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	apply_checker(t_obj obj, t_hit_record hit)
{
	t_vec2	distance;
	t_vec3	p_c;
	t_int2	count;

	if (obj.shape == SP)
	{
		count.x = (int)(hit.texture.x * 10) % 2;
		count.y = (int)(hit.texture.y * 10) % 2;
	}
	else if (obj.shape < CY)
	{
		p_c = v_minus(hit.point, obj.center);
		distance.x = v_dot(obj.storage.uv.u, p_c);
		distance.y = v_dot(obj.storage.uv.v, p_c);
		count.x = (int)fabs(distance.x / obj.storage.checker.x);
		count.y = (int)fabs(distance.y / obj.storage.checker.y);
		if (distance.x < 0)
			count.x++;
		if (distance.y < 0)
			count.y++;
	}
	if (obj.shape >= CY || ((count.x % 2 == 0) == (count.y % 2 == 0)))
		return (obj.color);
	return (obj.color_2);
}

t_vec3	apply_wave(t_vec3 phit, t_vec3 nhit)
{
	t_matrix	rot_m;
	double		angle;

	angle = (phit.x - (int)phit.x) * acos(-1.0) * 15;
	rot_m = create_rot_matrix(1, angle);
	return (v_rotation(rot_m, nhit));
}

t_vec3	apply_rainbow(t_vec3 obj_center, t_vec3 phit)
{
	t_vec3	normal;

	normal = v_unit_vector(v_minus(phit, obj_center));
	normal.x = (normal.x + 1.0) / 2.0;
	normal.y = (normal.y + 1.0) / 2.0;
	normal.z = (normal.z + 1.0) / 2.0;
	return (v_multiply_t(255, normal));
}
