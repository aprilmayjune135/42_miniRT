/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 09:31:04 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:09:06 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	set_v_t(t_vec3 a, t_vec3 b, t_vec3 origin, t_vec3 inv_dir)
{
	t_vec3	t;

	t.x = (a.x - origin.x) * inv_dir.x;
	if (inv_dir.x < 1e-8)
		t.x = (b.x - origin.x) * inv_dir.x;
	t.y = (a.y - origin.y) * inv_dir.y;
	if (inv_dir.y < 1e-8)
		t.y = (b.y - origin.y) * inv_dir.y;
	t.z = (a.z - origin.z) * inv_dir.z;
	if (inv_dir.z < 1e-8)
		t.z = (b.z - origin.z) * inv_dir.z;
	return (t);
}

int	cb_get_t(t_vec3 v_tmin, t_vec3 v_tmax, t_vec2 scope, double *t)
{
	double	tmin;
	double	tmax;

	tmin = v_tmin.x;
	tmax = v_tmax.x;
	if (tmin > v_tmax.y || tmax < v_tmin.y)
		return (-1);
	if (v_tmin.y > tmin)
		tmin = v_tmin.y;
	if (v_tmax.y < tmax)
		tmax = v_tmax.y;
	if (tmin > v_tmax.z || tmax < v_tmin.z)
		return (-1);
	if (v_tmin.z > tmin)
		tmin = v_tmin.z;
	if (v_tmax.z < tmax)
		tmax = v_tmax.z;
	*t = tmin;
	if (tmin < 1e-8 && tmax > 1e-8)
		*t = tmax;
	if (*t < scope.x || *t > scope.y)
		return (-1);
	return (1);
}

int	cb_intersect(t_obj cb, t_ray ray, t_vec2 scope, double *t)
{
	t_vec3	inv_dir;
	t_vec3	v_tmin;
	t_vec3	v_tmax;

	ray = rotate_ray(ray, cb.storage.w_to_l, cb.center);
	inv_dir = v_divide(create_vec3(1, 1, 1), ray.dir);
	v_tmin = set_v_t(cb.storage.uv.u, cb.storage.uv.v, ray.origin, inv_dir);
	v_tmax = set_v_t(cb.storage.uv.v, cb.storage.uv.u, ray.origin, inv_dir);
	return (cb_get_t(v_tmin, v_tmax, scope, t));
}

t_vec3	cb_nhit(t_obj cb, t_ray ray, double t)
{
	t_vec3	phit;
	t_vec3	near;
	t_vec3	far;
	t_vec3	normal;

	ray = rotate_ray(ray, cb.storage.w_to_l, cb.center);
	near = cb.storage.uv.u;
	far = cb.storage.uv.v;
	phit = ray_at(ray, t);
	if (fabs(phit.x - near.x) < 1e-8)
		normal = create_vec3(-1, 0, 0);
	else if (fabs(phit.y - near.y) < 1e-8)
		normal = create_vec3(0, -1, 0);
	else if (fabs(phit.z - near.z) < 1e-8)
		normal = create_vec3(0, 0, -1);
	else if (fabs(phit.x - far.x) < 1e-8)
		normal = create_vec3(1, 0, 0);
	else if (fabs(phit.y - far.y) < 1e-8)
		normal = create_vec3(0, 1, 0);
	else if (fabs(phit.z - far.z) < 1e-8)
		normal = create_vec3(0, 0, 1);
	else
		normal = create_vec3(0, 0, 0);
	return (v_rotation(cb.storage.l_to_w, normal));
}

int	cb_hit(t_obj cb, t_ray ray, t_hit_record *hit)
{
	double	t;
	t_vec3	normal;

	if (cb_intersect(cb, ray, hit->t_scope, &t) == -1)
		return (-1);
	normal = cb_nhit(cb, ray, t);
	process_hit(hit, ray, normal, t);
	return (1);
}
