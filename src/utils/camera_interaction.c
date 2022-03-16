/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera_interaction.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 20:26:09 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 19:28:26 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "key.h"

void	switch_camera(t_obj *current, t_obj *cameras)
{
	ft_putstr("Attention! You just switched the camera.\n");
	if (!current->next)
		*current = *cameras;
	else
		*current = *(current->next);
}

void	rotate_camera(t_obj *camera, int keycode, double delta, t_screen screen)
{
	t_vec3	rotate;

	ft_putstr("Rotating camera with key......\n");
	if (keycode == KEY_W)
		rotate = v_multiply_t(delta, v_unit_vector(screen.vertical));
	else if (keycode == KEY_S)
		rotate = v_multiply_t(delta * -1, v_unit_vector(screen.vertical));
	else if (keycode == KEY_D)
		rotate = v_multiply_t(delta, v_unit_vector(screen.horizontal));
	else
		rotate = v_multiply_t(delta * -1, v_unit_vector(screen.horizontal));
	camera->normal = v_unit_vector(v_add(screen.normal, rotate));
}

void	translate_camera(t_obj *camera, int keycode, double delta,
		t_screen screen)
{
	t_vec3	move;

	ft_putstr("Moving camera with key......\n");
	if (keycode == KEY_UP)
		move = v_multiply_t(delta, screen.vertical);
	else if (keycode == KEY_DOWN)
		move = v_multiply_t(delta * -1, screen.vertical);
	else if (keycode == KEY_RIGHT)
		move = v_multiply_t(delta, screen.horizontal);
	else if (keycode == KEY_LEFT)
		move = v_multiply_t(delta * -1, screen.horizontal);
	else if (keycode == KEY_E)
		move = v_multiply_t(delta, screen.normal);
	else
		move = v_multiply_t(delta * -1, screen.normal);
	camera->center = v_add(camera->center, move);
}

void	rotate_camera_mouse(t_obj *camera, t_int2 mouse,
	t_int2 image_size, t_screen screen)
{
	t_vec2		change;
	t_vec3		rotate;

	change.x = ((double)mouse.x - (double)image_size.x / 2.0)
		/ (double)image_size.x;
	change.y = ((double)image_size.y / 2.0 - (double)mouse.y)
		/ (double)image_size.y;
	rotate = v_add(v_multiply_t(change.x, screen.horizontal),
			v_multiply_t(change.y, screen.vertical));
	camera->normal = v_unit_vector(v_add(screen.normal, rotate));
}
