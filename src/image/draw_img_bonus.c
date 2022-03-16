/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_img_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 20:53:06 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 18:50:28 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec2	calculate_uv(t_int2 image, t_int2 image_size)
{
	t_vec2	uv;

	uv.x = (double)image.x / (double)(image_size.x - 1);
	uv.y = 1 - (double)image.y / (double)(image_size.y - 1);
	return (uv);
}

void	draw_thread(t_thread *thread)
{
	t_ray		ray;
	t_int2		image;
	t_vec2		uv;

	ray.origin = (thread->camera).center;
	image.y = 0;
	while (image.y < (thread->scene).image_size.y)
	{
		image.x = thread->index;
		while (image.x < (thread->scene).image_size.x)
		{
			uv = calculate_uv(image, (thread->scene).image_size);
			ray.dir = v_add(v_add((thread->screen).lower_left_corner,
						v_multiply_t(uv.x, (thread->screen).horizontal)),
					v_minus(v_multiply_t(uv.y, (thread->screen).vertical),
						ray.origin));
			my_mlx_pixel_put(thread->img, image.x, image.y,
				create_color(0, ray_trace(thread->scene, ray)));
			image.x += THREAD_COUNT;
		}
		image.y++;
	}
	pthread_exit(NULL);
}

void	draw_img(t_img *img, t_scene scene, t_obj camera, t_screen screen)
{
	pthread_t	pthread[THREAD_COUNT];
	t_thread	thread[THREAD_COUNT];
	int			i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		thread[i].index = i;
		thread[i].scene = scene;
		thread[i].camera = camera;
		thread[i].screen = screen;
		thread[i].img = img;
		pthread_create(&pthread[i], NULL, (void *)draw_thread, &thread[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}
}
