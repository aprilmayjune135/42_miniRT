/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 15:19:31 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:59:38 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	pl_intersect(t_obj pl, t_ray ray, t_vec2 scope, double *t)
{
	double	a;
	double	b;

	a = v_dot(pl.normal, ray.dir);
	if (fabs(a) < 1e-8)
		return (-1);
	b = v_dot(v_minus(pl.center, ray.origin), pl.normal);
	*t = b / a;
	if (*t < scope.x || *t > scope.y)
		return (-1);
	return (1);
}

int	pl_hit(t_obj pl, t_ray ray, t_hit_record *hit)
{
	double	t;

	if (pl_intersect(pl, ray, hit->t_scope, &t) == -1)
		return (-1);
	process_hit(hit, ray, pl.normal, t);
	return (1);
}

int	ds_intersect(t_obj ds, t_ray ray, t_vec2 scope, double *t)
{
	t_vec3	p_intersect;
	double	a;
	double	b;

	a = v_dot(ds.normal, ray.dir);
	if (fabs(a) < 1e-8)
		return (-1);
	b = v_dot(v_minus(ds.center, ray.origin), ds.normal);
	*t = b / a;
	if (*t < scope.x || *t > scope.y)
		return (-1);
	p_intersect = ray_at(ray, *t);
	if (v_length_squared(v_minus(p_intersect, ds.center))
		> ds.radius * ds.radius)
		return (-1);
	return (1);
}

int	ds_hit(t_obj ds, t_ray ray, t_hit_record *hit)
{
	double	t;

	if (ds_intersect(ds, ray, hit->t_scope, &t) == -1)
		return (-1);
	process_hit(hit, ray, ds.normal, t);
	return (1);
}
