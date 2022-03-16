/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 18:29:40 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/03 10:34:13 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	v_divide(t_vec3	v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	return (result);
}

double	v_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	v_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

double	v_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	v_length(t_vec3 v)
{
	return (sqrt(v_length_squared(v)));
}
