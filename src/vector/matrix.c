/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 13:52:10 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 17:44:07 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	create_matrix(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_matrix	result;

	result.row1 = v1;
	result.row2 = v2;
	result.row3 = v3;
	return (result);
}

t_matrix	m_multiply_t(double t, t_matrix m)
{
	t_matrix	result;

	result.row1 = v_multiply_t(t, m.row1);
	result.row2 = v_multiply_t(t, m.row2);
	result.row3 = v_multiply_t(t, m.row3);
	return (result);
}

t_matrix	m_add(t_matrix m1, t_matrix m2)
{
	t_matrix	result;

	result.row1 = v_add(m1.row1, m2.row1);
	result.row2 = v_add(m1.row2, m2.row2);
	result.row3 = v_add(m1.row3, m2.row3);
	return (result);
}

t_matrix	m_scaler(double a, double b, double c)
{
	t_matrix	m;

	m.row1 = create_vec3(a, 0, 0);
	m.row2 = create_vec3(0, b, 0);
	m.row3 = create_vec3(0, 0, c);
	return (m);
}
