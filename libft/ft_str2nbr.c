/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2nbr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 20:51:24 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:28:31 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_str2int(char *str, int j, int sign)
{
	unsigned long long int	power;
	unsigned long long int	output;
	int						len;

	output = 0;
	len = j;
	power = 1;
	while (len > 0)
	{
		output += (str[len - 1] - '0') * power;
		power *= 10;
		len--;
	}
	return (output * sign);
}

double	ft_str2double(char *str, int sign)
{
	int		pos;
	int		decimal;
	int		before_dot;
	int		after_dot;

	pos = 0;
	decimal = 0;
	while (str[pos] >= '0' && str[pos] <= '9')
		pos++;
	before_dot = ft_str2int(str, pos, sign);
	if (!str[pos])
		return ((double)before_dot);
	pos++;
	while (str[pos + decimal] >= '0' && str[pos + decimal] <= '9')
		decimal++;
	after_dot = ft_str2int(str + pos, decimal, sign);
	return (before_dot + (double)after_dot / ft_power_d(10.0, decimal));
}
