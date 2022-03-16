/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 17:38:08 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:01:00 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sq_intersect(t_obj sq, t_ray ray, t_vec2 scope, double *t)
{
	if (tr_intersect_check(sq.storage.tr[0], ray, scope, t) == 1
		|| tr_intersect_check(sq.storage.tr[1], ray, scope, t) == 1)
		return (1);
	return (-1);
}

int	sq_hit(t_obj sq, t_ray ray, t_hit_record *hit)
{
	double	t;

	if (sq_intersect(sq, ray, hit->t_scope, &t) == -1)
		return (-1);
	process_hit(hit, ray, sq.normal, t);
	return (1);
}
