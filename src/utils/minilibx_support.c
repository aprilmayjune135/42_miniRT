/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minilibx_support.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/19 11:16:16 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/16 12:33:24 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "key.h"

int	create_color(int t, t_vec3 color)
{
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	return (t << 24 | (int)(color.x + 0.5) << 16
			| (int)(color.y + 0.5) << 8 | (int)(color.z + 0.5));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_minirt *minirt)
{
	ft_putstr("You've just requested to exit program...\n");
	mlx_destroy_window(minirt->mlx, minirt->win);
	return (exit_program(minirt));
}

int	key_hook_minirt(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_SWITCH_CAMERA)
		switch_camera(&minirt->camera, minirt->scene->cameras);
	else if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		rotate_camera(&minirt->camera, keycode, CAMERA_MOVE, minirt->screen);
	else if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_E || keycode == KEY_Q)
		translate_camera(&minirt->camera, keycode, CAMERA_MOVE, minirt->screen);
	else if (keycode == KEY_EXIT)
		return (close_window(minirt));
	else
	{
		ft_putstr("Oops! You just pressed a useless key!\n");
		return (0);
	}
	display_img(minirt);
	return (0);
}

int	mouse_hook_minirt(int button, int x, int y, t_minirt *minirt)
{
	t_int2	mouse;
	int		scope;
	t_vec2	window;

	mouse.x = x;
	mouse.y = y;
	window.x = (double)minirt->scene->image_size.x;
	window.y = (double)minirt->scene->image_size.y;
	scope = 0;
	if (x > (int)(window.x * MOUSE_PROTECTION)
		&& x < (int)(window.x * (1 - MOUSE_PROTECTION))
		&& y > (int)(window.y * MOUSE_PROTECTION)
		&& y < (int)(window.y * (1 - MOUSE_PROTECTION)))
		scope = 1;
	if (button == 1 && scope == 1)
	{
		ft_putstr("Rotating camera with mouse......\n");
		rotate_camera_mouse(&minirt->camera, mouse,
			minirt->scene->image_size, minirt->screen);
		display_img(minirt);
	}
	if (button != 1)
		ft_putstr("Invalid mouse button.\n");
	return (0);
}
