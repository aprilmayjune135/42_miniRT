/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/30 16:04:57 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 15:07:30 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sp_intersect(t_obj sp, t_ray ray, t_vec2 scope, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	d;

	oc = v_minus(ray.origin, sp.center);
	a = v_length_squared(ray.dir);
	b = v_dot(oc, ray.dir);
	c = v_length_squared(oc) - sp.radius * sp.radius;
	d = b * b - a * c;
	if (d < 0)
		return (-1);
	*t = (b * -1 - sqrt(d)) / a;
	if (*t < scope.x || *t > scope.y)
	{
		*t = (b * -1 + sqrt(d)) / a;
		if (*t < scope.x || *t > scope.y)
			return (-1);
	}
	return (1);
}

int	sp_hit(t_obj sp, t_ray ray, t_hit_record *hit)
{
	double	t;
	t_vec3	normal;
	double	pi;

	pi = acos(-1.0);
	if (sp_intersect(sp, ray, hit->t_scope, &t) == -1)
		return (-1);
	hit->point = ray_at(ray, t);
	normal = v_multiply_t(1.0 / sp.radius,
			v_minus(hit->point, sp.center));
	process_hit(hit, ray, normal, t);
	hit->texture.x = (1 + atan2(hit->normal_out.z,
				hit->normal_out.x) / pi) * 0.5;
	hit->texture.y = acosf(hit->normal_out.y) / pi;
	return (1);
}
