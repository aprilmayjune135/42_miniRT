/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 13:36:10 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/16 00:09:25 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	hit_obj_color(t_obj obj, t_hit_record hit)
{
	if (obj.effect.checker == 1)
		return (apply_checker(obj, hit));
	if (obj.effect.rainbow == 1)
		return (apply_rainbow(obj.center, hit.point));
	return (obj.color);
}

void	process_hit_record(t_hit_record *hit, t_obj final, t_vec3 *bump_map)
{
	if (final.effect.bump == 1)
		hit->normal_out = bump_normal(final, *hit, bump_map);
	if (final.effect.wave == 1)
		hit->normal_out = apply_wave(hit->point, hit->normal_out);
	hit->obj_shape = final.shape;
	hit->obj_color = hit_obj_color(final, *hit);
	hit->obj_phong = final.phong;
}

int	hit_any(t_obj *objs, t_ray ray, t_hit_record *hit, t_vec3 *bump_map)
{
	t_obj	*obj_temp;
	int		hit_anything;
	t_obj	final;

	hit->t_scope.x = 0;
	hit->t_scope.y = 1.0 / 0.0;
	obj_temp = objs;
	hit_anything = 0;
	while (obj_temp != NULL)
	{
		if (ft_hit(*obj_temp, ray, hit) == 1)
		{
			hit_anything = 1;
			hit->t_scope.y = hit->t;
			final = *obj_temp;
		}
		obj_temp = obj_temp->next;
	}
	if (hit_anything == 1)
		process_hit_record(hit, final, bump_map);
	return (hit_anything);
}

t_vec3	filter_color(int type, t_vec3 surface)
{
	double	greyscale;
	t_vec3	filter;

	greyscale = (surface.x + surface.y + surface.z) / 3;
	if (type == 0)
		return (surface);
	if (type == (int)('R'))
		filter = create_vec3(1.4, 0.8, 0.8);
	else if (type == (int)('G'))
		filter = create_vec3(0.8, 1.4, 0.8);
	else if (type == (int)('B'))
		filter = create_vec3(0.8, 0.8, 1.4);
	else if (type == (int)('S'))
		filter = create_vec3(1.76, 0.95, 0.29);
	else
		filter = create_vec3(1, 1, 1);
	return (v_multiply_t(greyscale, filter));
}

t_vec3	ray_trace(t_scene scene, t_ray ray)
{
	t_vec3			surface;
	t_hit_record	hit;

	if (hit_any(scene.objs, ray, &hit, scene.bump) == 0)
		return (scene.back_color);
	surface = surface_color(scene, hit, ray.dir);
	surface = filter_color(scene.color_filter, surface);
	return (surface);
}
