/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_nbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 21:28:09 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:19:50 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	read_int(char *s, int *pos, int *nbr)
{
	int	sign;
	int	len_int;

	sign = 1;
	len_int = 0;
	while (ft_isspace(s[*pos]))
		(*pos)++;
	if (s[*pos] == '-')
	{
		sign = -1;
		(*pos)++;
	}
	while (ft_isdigit(s[*pos + len_int]))
		len_int++;
	if (!len_int)
		return (-1);
	*nbr = ft_str2int(s + *pos, len_int, sign);
	*pos = *pos + len_int;
	return (1);
}

int	read_decimal(char *s, int *pos, double *nbr)
{
	int	len_deci;

	len_deci = 0;
	while (ft_isdigit(s[*pos + len_deci]))
		len_deci++;
	if (!len_deci)
		return (-1);
	*nbr = (double)ft_str2int(s + *pos, len_deci, 1)
		/ ft_power_d(10, len_deci);
	*pos = *pos + len_deci;
	return (1);
}

/*
**	return -1 if no nbr is read in the str;
**	return 1 if nbr is read.
*/

int	read_double(char *s, int *pos, double *nbr)
{
	int		sign;
	int		nbr_int;
	double	nbr_decimal;

	sign = 1;
	while (ft_isspace(s[*pos]))
		(*pos)++;
	if (s[*pos] == '-')
	{
		sign = -1;
		(*pos)++;
	}
	nbr_int = 0;
	nbr_decimal = 0;
	if (read_int(s, pos, &nbr_int) == -1)
		return (-1);
	if (s[*pos] && s[*pos] == '.')
	{
		(*pos)++;
		if (read_decimal(s, pos, &nbr_decimal) == -1)
			return (-1);
	}
	*nbr = ((double)nbr_int + nbr_decimal) * (double)sign;
	return (1);
}

int	read_color(char *s, int *pos, t_vec3 *color)
{
	int	temp;

	if (read_int(s, pos, &temp) == -1 || temp < 0 || temp > 255)
		return (-1);
	color->x = (double)temp;
	if (s[*pos] != ',' || !ft_isdigit(s[*pos + 1]))
		return (-1);
	(*pos)++;
	if (read_int(s, pos, &temp) == -1 || temp < 0 || temp > 255)
		return (-1);
	color->y = (double)temp;
	if (s[*pos] != ',' || !ft_isdigit(s[*pos + 1]))
		return (-1);
	(*pos)++;
	if (read_int(s, pos, &temp) == -1 || temp < 0 || temp > 255)
		return (-1);
	color->z = (double)temp;
	return (1);
}

int	read_vec3(char *s, int *pos, t_vec3 *v)
{
	if (read_double(s, pos, &v->x) == -1)
		return (-1);
	if (s[*pos] != ',' || (!ft_isdigit(s[*pos + 1]) && s[*pos + 1] != '-'))
		return (-1);
	(*pos)++;
	if (read_double(s, pos, &v->y) == -1)
		return (-1);
	if (s[*pos] != ',' || (!ft_isdigit(s[*pos + 1]) && s[*pos + 1] != '-'))
		return (-1);
	(*pos)++;
	if (read_double(s, pos, &v->z) == -1)
		return (-1);
	return (1);
}
