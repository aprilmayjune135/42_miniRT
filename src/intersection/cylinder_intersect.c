/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_intersect.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 16:55:13 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:04:57 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** cy_on_body is to check if there is intersection point
** on the side of the cylinder,
** cy.center means the center point of the bottom surface.
*/

int	cy_on_body_find_root(t_ray new_ray, double diameter, t_vec2 *root)
{
	double		a;
	double		b;
	double		c;
	double		d;

	a = new_ray.dir.x * new_ray.dir.x + new_ray.dir.y * new_ray.dir.y;
	b = new_ray.origin.x * new_ray.dir.x + new_ray.origin.y * new_ray.dir.y;
	c = new_ray.origin.x * new_ray.origin.x
		+ new_ray.origin.y * new_ray.origin.y - diameter * diameter;
	d = b * b - a * c;
	if (d < 1e-8)
		return (-1);
	root->x = (b * -1.0 - sqrt(d)) / a;
	root->y = (b * -1.0 + sqrt(d)) / a;
	return (1);
}

int	co_on_body_find_root(t_ray new_ray, double diameter, double height,
						t_vec2 *root)
{
	double		a;
	double		b;
	double		c;
	double		d;
	t_vec2		e;

	e.x = diameter * new_ray.dir.z / height;
	e.y = diameter * (1.0 - new_ray.origin.z / height);
	a = new_ray.dir.x * new_ray.dir.x
		+ new_ray.dir.y * new_ray.dir.y - e.x * e.x;
	b = new_ray.origin.x * new_ray.dir.x
		+ new_ray.origin.y * new_ray.dir.y + e.x * e.y;
	c = new_ray.origin.x * new_ray.origin.x
		+ new_ray.origin.y * new_ray.origin.y - e.y * e.y;
	d = b * b - a * c;
	if (d < 1e-8)
		return (-1);
	root->x = (b * -1.0 - sqrt(d)) / a;
	root->y = (b * -1.0 + sqrt(d)) / a;
	return (1);
}

int	cyco_get_t(int x1, int x2, t_vec2 root, double *t)
{
	if (x1 == 0 && x2 == 0)
		return (-1);
	else if (x1 == 1 && x2 == 1)
		*t = ft_min_double(2, root.x, root.y);
	else if (x1 == 1 && x2 == 0)
		*t = root.x;
	else
		*t = root.y;
	return (x1 + x2);
}

int	cyco_on_body(t_ray new_ray, t_obj obj, double *t)
{
	t_vec3		p;
	t_vec2		root;
	int			x1;
	int			x2;

	if (obj.shape == CY)
	{
		if (cy_on_body_find_root(new_ray, obj.radius, &root) == -1)
			return (-1);
	}
	if (obj.shape == CO)
	{
		if (co_on_body_find_root(new_ray,
				obj.radius, obj.size_3d.y, &root) == -1)
			return (-1);
	}
	p = ray_at(new_ray, root.x);
	x1 = 0;
	x2 = 0;
	if (root.x > 1e-8 && p.z > 1e-8 && p.z < obj.size_3d.y)
		x1 = 1;
	p = ray_at(new_ray, root.y);
	if (root.y > 1e-8 && p.z > 1e-8 && p.z < obj.size_3d.y)
		x2 = 1;
	return (cyco_get_t(x1, x2, root, t));
}

/*
** cy_intersect_body returns -1 if there is no intersection,
** otherwise it returns the number of intersection points (1 or 2) on the body.
*/

int	cyco_intersect_body(t_obj cy, t_ray ray, t_vec2 scope, double *t_body)
{
	t_ray	new_ray;
	int		result;

	new_ray = rotate_ray(ray, cy.storage.w_to_l, cy.center);
	result = cyco_on_body(new_ray, cy, t_body);
	if (result == -1)
		return (-1);
	if (*t_body < scope.x || *t_body > scope.y)
		return (-1);
	return (result);
}
