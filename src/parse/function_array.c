/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_array.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 18:07:13 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 18:19:05 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_environment(char *s)
{
	if (s[0] == 'F' && ft_isspace(s[1]))
		return (-3);
	if (s[0] == 'R' && ft_isspace(s[1]))
		return (-2);
	if (s[0] == 'A' && ft_isspace(s[1]))
		return (-1);
	if (s[0] == 'c' && ft_isspace(s[1]))
		return (0);
	if (s[0] == 'l' && ft_isspace(s[1]))
		return (1);
	if (s[0] == 'd' && s[1] == 'l' && ft_isspace(s[2]))
		return (2);
	return (-10);
}

int	get_obj_shape(char *s)
{
	if (s[0] == 's' && s[1] == 'p' && ft_isspace(s[2]))
		return (SP);
	if (s[0] == 'p' && s[1] == 'l' && ft_isspace(s[2]))
		return (PL);
	if (s[0] == 't' && s[1] == 'r' && ft_isspace(s[2]))
		return (TR);
	if (s[0] == 's' && s[1] == 'q' && ft_isspace(s[2]))
		return (SQ);
	if (s[0] == 'c' && s[1] == 'y' && ft_isspace(s[2]))
		return (CY);
	if (s[0] == 'd' && s[1] == 's' && ft_isspace(s[2]))
		return (DS);
	if (s[0] == 'c' && s[1] == 'o' && ft_isspace(s[2]))
		return (CO);
	if (s[0] == 'c' && s[1] == 'b' && ft_isspace(s[2]))
		return (CB);
	if (s[0] == 'p' && s[1] == 'r' && ft_isspace(s[2]))
		return (PR);
	return (get_environment(s));
}

int	ft_parse_obj(char *s, t_obj *new, int shape)
{
	int	(*ft[13])(char *, t_obj *);

	ft[0] = parse_camera;
	ft[1] = parse_spot_light;
	ft[2] = parse_dir_light;
	ft[SP] = parse_sp;
	ft[PL] = parse_pl;
	ft[TR] = parse_tr;
	ft[SQ] = parse_sq;
	ft[CY] = parse_cy;
	ft[DS] = parse_ds;
	ft[CO] = parse_cy;
	ft[CB] = parse_cb;
	ft[PR] = parse_cy;
	return ((*ft[shape])(s, new));
}

int	ft_intersect(t_obj obj, t_ray ray_light, t_vec2 t_scope, double *t)
{
	int	(*ft[13])(t_obj, t_ray, t_vec2, double *);

	ft[SP] = sp_intersect;
	ft[PL] = pl_intersect;
	ft[TR] = tr_intersect;
	ft[SQ] = sq_intersect;
	ft[CY] = cyco_intersect;
	ft[DS] = ds_intersect;
	ft[CO] = cyco_intersect;
	ft[CB] = cb_intersect;
	ft[PR] = pr_intersect;
	return ((*ft[obj.shape])(obj, ray_light, t_scope, t));
}

int	ft_hit(t_obj obj, t_ray ray, t_hit_record *hit)
{
	int	(*ft[13])(t_obj, t_ray, t_hit_record *);

	ft[SP] = sp_hit;
	ft[PL] = pl_hit;
	ft[TR] = tr_hit;
	ft[SQ] = sq_hit;
	ft[CY] = cyco_hit;
	ft[DS] = ds_hit;
	ft[CO] = cyco_hit;
	ft[CB] = cb_hit;
	ft[PR] = pr_hit;
	return ((*ft[obj.shape])(obj, ray, hit));
}
