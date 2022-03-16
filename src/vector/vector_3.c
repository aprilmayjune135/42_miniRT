/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_3.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 14:13:36 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 17:43:53 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	v_unit_vector(t_vec3 v)
{
	double	t;

	t = 1 / v_length(v);
	return (v_multiply_t(t, v));
}

t_vec2	create_vec2(double x, double y)
{
	t_vec2	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (v_add(ray.origin, v_multiply_t(t, ray.dir)));
}

t_vec3	pl_arbitrary_p(t_vec3 normal)
{
	t_vec3	new;

	new = create_vec3(1, 1, 1);
	if (fabs(normal.x) > 1e-8)
		new.x = -1.0 * (normal.y * new.y + normal.z * new.z) / normal.x;
	else if (fabs(normal.y) > 1e-8)
		new.y = -1.0 * (normal.x * new.x + normal.z * new.z) / normal.y;
	else if (fabs(normal.z) > 1e-8)
		new.z = -1.0 * (normal.x * new.x + normal.y * new.y) / normal.z;
	return (v_unit_vector(new));
}
