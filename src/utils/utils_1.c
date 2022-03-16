/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 14:00:50 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 15:08:00 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	convert_rad(int angle)
{
	double	pi;

	pi = acos(-1.0);
	return (pi * angle / 180);
}

double	convert_angle(double rad)
{
	double	pi;

	pi = acos(-1.0);
	return (rad * 180 / pi);
}

int	obj_list_len(t_obj *list)
{
	t_obj	*temp;
	int		len;

	len = 0;
	temp = list;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}

/*
** reflection (R), incident(I), surface normal(N):
** R = I - 2 * (I.N) * N
*/

t_vec3	reflection_dir(t_vec3 ray_dir, t_vec3 hit_normal)
{
	t_vec3	result;

	result = v_multiply_t(2, hit_normal);
	result = v_multiply_t(v_dot(ray_dir, hit_normal), result);
	result = v_minus(ray_dir, result);
	return (result);
}
