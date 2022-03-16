/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 13:58:34 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 17:41:30 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec3	v_multiply_t(double t, t_vec3 orig)
{
	t_vec3	result;

	result.x = t * orig.x;
	result.y = t * orig.y;
	result.z = t * orig.z;
	return (result);
}

t_vec3	v_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec3	v_minus(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec3	v_multiply(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}
