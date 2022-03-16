/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_cone.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 17:43:28 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:58:47 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** cy_intersect_disc returns -1 if there is no intersection
** on the top or bottom surface, otherwise it returns
** the number of intersection points (1 or 2).
** cy.center means the center point of the bottom surface.
*/

int	cy_intersect_disc(t_obj cy, t_ray ray, t_vec2 scope, double *t_disc)
{
	t_vec2	root;

	if (ds_intersect(cy, ray, scope, &root.x) == -1)
		root.x = -1;
	cy.center = v_add(cy.center, v_multiply_t(cy.size_3d.y, cy.normal));
	if (ds_intersect(cy, ray, scope, &root.y) == -1)
		root.y = -1;
	if (root.x < 0 && root.y < 0)
		return (-1);
	if (root.x > 1e-8 && root.y > 1e-8)
	{
		*t_disc = ft_min_double(2, root.x, root.y);
		return (2);
	}
	*t_disc = ft_max_double(2, root.x, root.y);
	return (1);
}

int	co_intersect_disc(t_obj co, t_ray ray, t_vec2 scope, double *t_disc)
{
	if (ds_intersect(co, ray, scope, t_disc) == -1)
		return (-1);
	return (1);
}

/*
** cy_intersect
** returns -1 if there is no intersection either on the body or the discs,
** it returns 1 if the nearest intersection point is on the body,
** it returns 2 if the nearest intersection point is on the top/bottom discs.
*/

int	cyco_intersect(t_obj cy, t_ray ray, t_vec2 scope, double *t)
{
	int		i_disc;
	int		i_body;
	double	t_body;

	if (cy.shape == CY)
		i_disc = cy_intersect_disc(cy, ray, scope, t);
	if (cy.shape == CO)
		i_disc = co_intersect_disc(cy, ray, scope, t);
	if (i_disc == 2)
		return (2);
	i_body = cyco_intersect_body(cy, ray, scope, &t_body);
	if (i_disc == -1 && i_body == -1)
		return (-1);
	if (i_body == 2 || i_disc == -1
		|| (i_disc > 0 && i_body > 0 && t_body < *t))
	{
		*t = t_body;
		return (1);
	}
	return (2);
}

t_vec3	cyco_hit_normal(t_obj cy, t_vec3 phit)
{
	t_vec3	top;
	t_vec3	p2;

	top = v_add(cy.center, v_multiply_t(cy.size_3d.y, cy.normal));
	if (cy.shape == CY)
		return (v_unit_vector(v_cross(cy.normal, v_cross(
						v_minus(top, phit), v_minus(cy.center, phit)))));
	p2 = v_add(top, v_multiply_t(cy.size_3d.y * cos(atan(cy.radius
						/ cy.size_3d.y)), v_unit_vector(v_minus(phit, top))));
	return (v_unit_vector(v_minus(p2, cy.center)));
}

int	cyco_hit(t_obj cy, t_ray ray, t_hit_record *hit)
{
	double	t;
	int		isec;

	isec = cyco_intersect(cy, ray, hit->t_scope, &t);
	if (isec == -1)
		return (-1);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->front_face = 1;
	if (isec == 2)
		hit->normal_out = cy.normal;
	else
		hit->normal_out = cyco_hit_normal(cy, hit->point);
	if (v_dot(hit->normal_out, ray.dir) > 1e-8)
	{
		hit->normal_out = v_multiply_t(-1, hit->normal_out);
		hit->front_face = -1;
	}
	return (1);
}
