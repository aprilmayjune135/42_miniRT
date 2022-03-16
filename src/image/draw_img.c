/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_img.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 20:53:06 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 19:32:08 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_img(t_img *img, t_scene scene, t_obj camera, t_screen screen)
{
	t_ray		ray;
	t_int2		image;
	t_vec2		uv;

	ray.origin = camera.center;
	image.y = 0;
	while (image.y < scene.image_size.y)
	{
		image.x = 0;
		while (image.x < scene.image_size.x)
		{
			uv.x = (double)image.x / (double)(scene.image_size.x - 1);
			uv.y = 1 - (double)image.y / (double)(scene.image_size.y - 1);
			ray.dir = v_add(v_add(screen.lower_left_corner,
						v_multiply_t(uv.x, screen.horizontal)),
					v_minus(v_multiply_t(uv.y, screen.vertical), ray.origin));
			my_mlx_pixel_put(img, image.x, image.y,
				create_color(0, ray_trace(scene, ray)));
			image.x++;
		}
		image.y++;
	}
}
