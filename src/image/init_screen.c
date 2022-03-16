/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 12:36:49 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 17:48:15 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_std_screen(t_screen *std, double fov, t_int2 image_size)
{
	std->eye_to_screen = EYE_TO_SCREEN;
	std->viewport.x = 2 * std->eye_to_screen * tan(convert_rad(fov / 2))
		* (std->z * -1);
	std->viewport.y = fabs(std->viewport.x / (double)image_size.x
			* (double)image_size.y);
	std->horizontal = create_vec3(std->viewport.x, 0, 0);
	std->vertical = create_vec3(0, std->viewport.y, 0);
}

void	init_screen(t_screen *screen, t_obj camera, t_int2 image_size)
{
	t_matrix	rotate;

	if (camera.normal.z > 0)
		screen->z = 1;
	else
		screen->z = -1;
	set_std_screen(screen, camera.radius, image_size);
	rotate = m_rotation(create_vec3(0, 0, screen->z), camera.normal);
	screen->normal = v_multiply_t(screen->eye_to_screen, camera.normal);
	screen->horizontal = v_rotation(rotate, screen->horizontal);
	screen->vertical = v_rotation(rotate, screen->vertical);
	screen->lower_left_corner = v_minus(v_add(camera.center, screen->normal),
			v_add(v_multiply_t(0.5, screen->horizontal),
				v_multiply_t(0.5, screen->vertical)));
}
