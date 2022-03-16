/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surface_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 18:44:14 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 22:03:34 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** get_transmissoin:
** 1) ray_light.origin is defined by adjusting hit->point with a bias of 1e-4
** in order to avoid surface edge discrepancy;
** 2) returns 0 if intersected - an obj is between hit->point and light source,
** and returns 1 if there is no interesection when trace back to light source.
*/

double	get_transmission(t_vec3 light_dir, t_hit_record hit, t_obj *objs)
{
	t_obj			*obj_temp;
	t_ray			ray_light;
	t_hit_record	hit_temp;

	obj_temp = objs;
	hit_temp.t_scope.x = 0;
	hit_temp.t_scope.y = v_length(light_dir);
	ray_light.origin = v_add(hit.point, v_multiply_t(1e-4, hit.normal_out));
	ray_light.dir = v_unit_vector(light_dir);
	while (obj_temp != NULL)
	{
		if (ft_intersect(*obj_temp, ray_light, hit_temp.t_scope, &hit_temp.t)
			> -1)
			return (0);
		obj_temp = obj_temp->next;
	}
	return (1);
}

t_vec3	diffuse_trace_light(t_obj light, t_hit_record hit, t_obj *objs)
{
	t_vec3	light_dir;
	double	transmission;
	double	i;
	t_vec3	light_color_index;

	if (light.shape == 1)
		light_dir = v_minus(light.center, hit.point);
	else
		light_dir = v_multiply_t(-1, light.normal);
	transmission = get_transmission(light_dir, hit, objs);
	i = v_dot(hit.normal_out, v_unit_vector(light_dir));
	if (i < 1e-8)
		i = 0;
	light_color_index = v_multiply_t(transmission
			* i / 255.0, light.color);
	return (v_multiply(light_color_index, hit.obj_color));
}

t_vec3	specular_trace_light(t_obj light, t_hit_record hit, t_obj *objs,
								t_vec3 ray_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	transmission;
	double	specular;
	t_vec2	index;

	if (light.shape == 1)
		light_dir = v_minus(light.center, hit.point);
	else
		light_dir = v_multiply_t(-1, light.normal);
	reflect_dir = reflection_dir(v_unit_vector(light_dir), hit.normal_out);
	transmission = get_transmission(light_dir, hit, objs);
	index.x = v_dot(hit.normal_out, v_unit_vector(light_dir));
	if (index.x < 1e-8)
		index.x = 0;
	index.y = v_dot(ray_dir, reflect_dir);
	if (index.y < 1e-8)
		index.y = 0;
	specular = transmission * index.x * pow(index.y, hit.obj_phong.z);
	return (v_multiply_t(specular, light.color));
}

t_vec3	surface_color(t_scene scene, t_hit_record hit, t_vec3 ray_dir)
{
	t_obj	*light_temp;
	t_vec3	diffuse_color;
	t_vec3	specular_color;

	light_temp = scene.lights;
	diffuse_color = v_multiply(v_multiply_t(1.0 / 255.0,
				scene.ambient_light), hit.obj_color);
	specular_color = create_vec3(0, 0, 0);
	while (light_temp != NULL)
	{
		diffuse_color = v_add(diffuse_color,
				diffuse_trace_light(*light_temp, hit, scene.objs));
		specular_color = v_add(specular_color,
				specular_trace_light(*light_temp, hit, scene.objs, ray_dir));
		light_temp = light_temp->next;
	}
	return (v_add(v_multiply_t(hit.obj_phong.x, diffuse_color),
			v_multiply_t(hit.obj_phong.y, specular_color)));
}
