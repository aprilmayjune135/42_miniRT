/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 19:19:48 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 22:03:04 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	tr_intersect_check(t_tr tr, t_ray ray, t_vec2 scope, double *t)
{
	t_vec3	ray_x_ac;
	t_vec3	ra;
	t_vec3	ra_x_ab;
	t_vec2	uv;
	double	det;

	ray_x_ac = v_cross(ray.dir, tr.ac);
	det = v_dot(tr.ab, ray_x_ac);
	if (fabs(det) < 1e-8)
		return (0);
	ra = v_minus(ray.origin, tr.a);
	uv.x = v_dot(ra, ray_x_ac) / det;
	if (uv.x < 0 || uv.x > 1)
		return (0);
	ra_x_ab = v_cross(ra, tr.ab);
	uv.y = v_dot(ray.dir, ra_x_ab) / det;
	if (uv.y < 0 || uv.x + uv.y > 1)
		return (0);
	*t = v_dot(tr.ac, ra_x_ab) / det;
	if (*t < scope.x || *t > scope.y)
		return (0);
	return (1);
}

int	tr_intersect(t_obj tr, t_ray ray, t_vec2 scope, double *t)
{
	if (tr_intersect_check(tr.storage.tr[0], ray, scope, t) < 1)
		return (-1);
	return (1);
}

int	tr_hit(t_obj tr, t_ray ray, t_hit_record *hit)
{
	double	t;

	if (tr_intersect(tr, ray, hit->t_scope, &t) == -1)
		return (-1);
	process_hit(hit, ray, tr.normal, t);
	return (1);
}
