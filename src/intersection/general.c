/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 18:31:21 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:59:26 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	process_hit(t_hit_record *hit, t_ray ray, t_vec3 obj_normal, double t)
{
	hit->t = t;
	hit->point = ray_at(ray, t);
	if (v_dot(obj_normal, ray.dir) > 0)
	{
		hit->front_face = -1;
		hit->normal_out = v_multiply_t(-1.0, obj_normal);
	}
	else
	{
		hit->front_face = 1;
		hit->normal_out = obj_normal;
	}
}
