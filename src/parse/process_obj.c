/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_obj.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 20:25:53 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 20:05:53 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	sq_point(t_vec3 center, t_vec3 dir_diagonal, double radius)
{
	t_vec3	new;

	new = v_multiply_t(sqrt(2.0) * radius / 2.0, dir_diagonal);
	return (v_add(center, new));
}

void	process_sq(t_obj *obj)
{
	t_vec3	dir_diagonal;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;

	dir_diagonal = pl_arbitrary_p(obj->normal);
	a = sq_point(obj->center, dir_diagonal, obj->radius);
	b = sq_point(obj->center,
			v_cross(obj->normal, dir_diagonal), obj->radius);
	c = v_add(obj->center, v_minus(obj->center, b));
	d = v_add(obj->center, v_minus(obj->center, a));
	obj->storage.tr[0] = create_tr(a, b, c);
	obj->storage.tr[1] = create_tr(d, c, b);
}

void	process_pr(t_obj *obj)
{
	double	r;
	double	h;

	r = obj->radius / sqrt(2.0);
	h = obj->size_3d.y;
	obj->storage.tr[0] = create_tr(create_vec3(0, 0, h),
			create_vec3(r, 0, 0), create_vec3(0, r, 0));
	obj->storage.tr[1] = create_tr(create_vec3(0, 0, h),
			create_vec3(0, r, 0), create_vec3(r * -1.0, 0, 0));
	obj->storage.tr[2] = create_tr(create_vec3(0, 0, h),
			create_vec3(r * -1.0, 0, 0), create_vec3(0, r * -1.0, 0));
	obj->storage.tr[3] = create_tr(create_vec3(0, 0, h),
			create_vec3(0, r * -1.0, 0), create_vec3(r, 0, 0));
	obj->storage.l_to_w = m_rotation(create_vec3(0, 0, 1), obj->normal);
}

void	process_ck(t_obj *obj)
{
	t_vec3	t_temp;

	obj->color_2 = create_vec3(255, 255, 255);
	if (obj->shape == PL || obj->shape == TR
		|| obj->shape == SQ || obj-> shape == DS)
	{
		t_temp = pl_arbitrary_p(obj->normal);
		obj->storage.uv.u = v_unit_vector(v_minus(t_temp, obj->center));
		obj->storage.uv.v = v_unit_vector(v_cross(obj->storage.uv.u,
					obj->normal));
		obj->storage.checker.x = 0.1;
		obj->storage.checker.y = 0.1;
	}
}

void	process_cb(t_obj *obj)
{
	obj->storage.w_to_l = m_rotation(obj->normal, create_vec3(0, 1, 0));
	obj->storage.l_to_w = m_rotation(create_vec3(0, 1, 0), obj->normal);
	obj->storage.uv.u = v_multiply_t(-0.5, obj->size_3d);
	obj->storage.uv.v = v_multiply_t(0.5, obj->size_3d);
}
