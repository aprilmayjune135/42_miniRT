/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_effect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 10:27:00 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:43:39 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_effect(t_effect *effect)
{
	effect->checker = 0;
	effect->wave = 0;
	effect->rainbow = 0;
	effect->bump = 0;
}

int	check_letter(char *s, int *pos, char *letters, int *effect)
{
	if (ft_strncmp(s + *pos, letters, 2) == 0)
	{
		(*effect)++;
		(*pos) += 2;
		return (1);
	}
	return (0);
}

int	read_effect(char *s, int *pos, t_effect *effect)
{
	init_effect(effect);
	while (ft_isspace(s[*pos]))
		(*pos)++;
	while (s[*pos])
	{
		if (!check_letter(s, pos, "ck", &effect->checker)
			&& !check_letter(s, pos, "wv", &effect->wave)
			&& !check_letter(s, pos, "rb", &effect->rainbow)
			&& !check_letter(s, pos, "bp", &effect->bump))
			return (-1);
		if (effect->checker > 1 || effect->wave > 1
			|| effect->rainbow > 1 || effect->bump > 1 )
			return (-1);
		while (ft_isspace(s[*pos]))
			(*pos)++;
	}
	return (1);
}
