/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   show_on.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 19:44:34 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/16 16:36:25 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	adjust_img_size(t_minirt *minirt)
{
	t_int2	origin_size;
	t_int2	display_size;

	origin_size = minirt->scene->image_size;
	mlx_get_screen_size(minirt->mlx, &display_size.x, &display_size.y);
	if (origin_size.x > display_size.x || origin_size.y > display_size.y)
	{
		minirt->scene->image_size.x = display_size.x;
		minirt->scene->image_size.y = display_size.y;
	}	
}

void	create_img(t_minirt *minirt)
{
	minirt->img.img = mlx_new_image(minirt->mlx,
			minirt->scene->image_size.x, minirt->scene->image_size.y);
	minirt->img.addr = mlx_get_data_addr(minirt->img.img,
			&minirt->img.bits_per_pixel, &minirt->img.line_length,
			&minirt->img.endian);
	init_screen(&minirt->screen, minirt->camera, minirt->scene->image_size);
	draw_img(&minirt->img, *(minirt->scene), minirt->camera, minirt->screen);
}

void	display_img(t_minirt *minirt)
{
	create_img(minirt);
	mlx_clear_window(minirt->mlx, minirt->win);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
	mlx_destroy_image(minirt->mlx, minirt->img.img);
}

void	show_on(char *name, t_minirt *minirt)
{
	minirt->mlx = mlx_init();
	minirt->camera = *(minirt->scene->cameras);
	adjust_img_size(minirt);
	if (minirt->save_bmp == 1)
		export_bmp(minirt);
	minirt->win = mlx_new_window(minirt->mlx, minirt->scene->image_size.x,
			minirt->scene->image_size.y, name);
	display_img(minirt);
	mlx_hook(minirt->win, 2, 1L << 0, key_hook_minirt, minirt);
	mlx_hook(minirt->win, 4, 1L << 3, mouse_hook_minirt, minirt);
	mlx_hook(minirt->win, 17, 1L << 2, close_window, minirt);
	mlx_loop(minirt->mlx);
}
