/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 16:25:52 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 21:02:50 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	set_phong(int shape)
{
	double	ks;
	double	kd;
	double	n;

	ks = 0.2;
	kd = 1 - ks;
	n = 22;
	if (shape != SP && shape != CY && shape != CO)
		return (create_vec3(1.0, 0, n));
	return (create_vec3(kd, ks, n));
}

void	process_obj(t_obj *obj)
{
	if (obj->shape == SP || obj->shape == CY || obj->shape == CO
		|| obj->shape == DS)
		obj->radius /= 2.0;
	if (obj->shape == SQ)
		process_sq(obj);
	if (obj->shape == PR)
		process_pr(obj);
	if (obj->shape == CB)
		process_cb(obj);
	if (obj->effect.checker == 1 || obj->effect.bump == 1)
		process_ck(obj);
}

int	parse_obj(char *s, t_obj **objs, int shape)
{
	t_obj	*add;
	t_obj	*temp;

	add = (t_obj *)malloc(sizeof(t_obj));
	if (!add)
		return (return_error(-1, "Malloc error in objects!\n"));
	if (ft_parse_obj(s, add, shape) == -1)
		return (-1);
	add->shape = shape;
	process_obj(add);
	add->phong = set_phong(shape);
	add->next = NULL;
	add->index = 0;
	if (!*objs)
		*objs = add;
	else
	{
		temp = *objs;
		while (temp->next)
			temp = temp->next;
		temp->next = add;
		add->index = temp->index + 1;
	}
	return (1);
}
