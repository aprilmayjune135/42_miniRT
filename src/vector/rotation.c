/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:07:05 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 17:43:29 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	create_rot_matrix(int axis, double angle)
{
	t_vec3	row1;
	t_vec3	row2;
	t_vec3	row3;

	if (axis == 1)
	{
		row1 = create_vec3(1, 0, 0);
		row2 = create_vec3(0, cos(angle), sin(angle));
		row3 = create_vec3(0, -sin(angle), cos(angle));
	}
	else if (axis == 2)
	{
		row1 = create_vec3(cos(angle), 0, -sin(angle));
		row2 = create_vec3(0, 1, 0);
		row3 = create_vec3(sin(angle), 0, cos(angle));
	}
	else
	{
		row1 = create_vec3(cos(angle), sin(angle), 0);
		row2 = create_vec3(-sin(angle), cos(angle), 0);
		row3 = create_vec3(0, 0, 1);
	}
	return (create_matrix(row1, row2, row3));
}

t_matrix	m_rotation(t_vec3 old, t_vec3 new)
{
	t_vec3		axis;
	double		cos;
	double		sin;
	t_matrix	m_a;
	t_matrix	m_b;

	axis = v_cross(new, old);
	cos = v_dot(new, old);
	if (fabs(cos - 1) < 1e-8)
		return (m_scaler(1, 1, 1));
	if (fabs(cos + 1) < 1e-8)
		axis = create_vec3(1, 0, 0);
	axis = v_unit_vector(axis);
	sin = sqrt(1 - cos * cos);
	m_a = create_matrix(v_multiply_t(axis.x, axis),
			v_multiply_t(axis.y, axis), v_multiply_t(axis.z, axis));
	m_b = create_matrix(create_vec3(0, -1 * axis.z, axis.y),
			create_vec3(axis.z, 0, -1 * axis.x),
			create_vec3(-1 * axis.y, axis.x, 0));
	return (m_add(m_add(m_scaler(cos, cos, cos),
				m_multiply_t(1 - cos, m_a)), m_multiply_t(sin, m_b)));
}

t_vec3	v_rotation(t_matrix m, t_vec3 v_old)
{
	t_vec3	v_new;

	v_new.x = v_old.x * m.row1.x + v_old.y * m.row2.x + v_old.z * m.row3.x;
	v_new.y = v_old.x * m.row1.y + v_old.y * m.row2.y + v_old.z * m.row3.y;
	v_new.z = v_old.x * m.row1.z + v_old.y * m.row2.z + v_old.z * m.row3.z;
	return (v_new);
}

t_ray	rotate_ray(t_ray ray, t_matrix	w_to_l, t_vec3 obj_center)
{
	t_ray		new_ray;

	new_ray.dir = v_rotation(w_to_l, ray.dir);
	new_ray.origin = v_rotation(w_to_l, v_minus(ray.origin, obj_center));
	return (new_ray);
}
