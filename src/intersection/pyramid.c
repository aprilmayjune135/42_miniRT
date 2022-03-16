/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pyramid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 15:41:10 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:00:15 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	pr_pick_root(int *isec, double *root, double *t, int count)
{
	int		i;
	int		result;

	*t = 1.0 / 0.0;
	i = 0;
	result = -1;
	while (i < count)
	{
		if (*(isec + i) == 1 && *(root + i) < *t)
		{
			*t = *(root + i);
			result = i;
		}
		i++;
	}
	return (result);
}

int	pr_check_square(double radius, t_ray ray, t_vec2 scope, double *t)
{
	double	x;
	double	y;
	double	r;

	if (fabs(ray.dir.z) < 1e-8)
		return (0);
	*t = -1.0 * ray.origin.z / ray.dir.z;
	if (*t < scope.x || *t > scope.y)
		return (0);
	r = radius / sqrt(2.0);
	x = ray.origin.x + *t * ray.dir.x;
	if (fabs(x) > r)
		return (0);
	y = ray.origin.y + *t * ray.dir.y;
	if (fabs(x) + fabs(y) > r)
		return (0);
	return (1);
}

int	pr_intersect(t_obj pr, t_ray ray, t_vec2 scope, double *t)
{
	t_ray	new_ray;
	int		result;
	int		isec[5];
	double	root[5];
	int		i;

	new_ray = rotate_ray(ray, pr.storage.w_to_l, pr.center);
	result = 0;
	i = 0;
	while (i < 4)
	{
		isec[i] = tr_intersect_check(pr.storage.tr[i],
				new_ray, scope, &root[i]);
		result += isec[i];
		if (result == 2)
			return (pr_pick_root(isec, root, t, i + 1));
		i++;
	}
	isec[4] = pr_check_square(pr.radius, new_ray, scope, &root[4]);
	return (pr_pick_root(isec, root, t, 5));
}

int	pr_hit(t_obj pr, t_ray ray, t_hit_record *hit)
{
	double	t;
	int		isec;
	t_vec3	normal;

	isec = pr_intersect(pr, ray, hit->t_scope, &t);
	if (isec == -1)
		return (-1);
	if (isec < 4)
		normal = v_rotation(pr.storage.l_to_w,
				pr.storage.tr[isec].normal);
	else
		normal = pr.normal;
	process_hit(hit, ray, normal, t);
	return (1);
}
