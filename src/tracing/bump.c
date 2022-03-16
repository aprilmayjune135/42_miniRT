/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:49:19 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:43:54 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	perturb_normal(t_vec3 nhit, t_vec3 nmap)
{
	t_matrix	l_to_w;

	l_to_w = m_rotation(create_vec3(0, 0, 1), nhit);
	return (v_rotation(l_to_w, nmap));
}

t_vec3	bump_normal(t_obj obj, t_hit_record hit, t_vec3 *bump_map)
{
	t_vec2	distance;
	t_vec3	p_c;
	t_int2	count;

	if (obj.shape >= CY || obj.shape == TR)
		return (hit.normal_out);
	if (obj.shape == SP)
	{
		count.x = (int)(hit.texture.x * 256 * BUMP_SCALE) % 256;
		count.y = (int)(hit.texture.y * 256 * BUMP_SCALE) % 256;
	}
	else
	{
		p_c = v_minus(hit.point, obj.center);
		distance.x = v_dot(obj.storage.uv.u, p_c);
		distance.y = v_dot(obj.storage.uv.v, p_c);
		count.x = (int)(fabs(distance.x) * 256 * BUMP_SCALE) % 256;
		count.y = (int)(fabs(distance.y) * 256 * BUMP_SCALE) % 256;
	}
	return (perturb_normal(hit.normal_out,
			*(bump_map + count.y * 256 + count.x)));
}
