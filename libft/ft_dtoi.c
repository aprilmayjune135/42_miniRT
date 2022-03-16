/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dtoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 16:17:02 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:26:35 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_dtoi(double n)
{
	long long int	i;
	int				sign;

	if (n == 0)
		return (0);
	if (n > 0)
		sign = 1;
	if (n < 0)
	{
		sign = -1;
		n *= -1;
	}
	i = (long long int)n;
	if (n - i >= 0.5)
		i++;
	return (i * sign);
}

double	ft_first_digit(double n)
{
	if (n < 10)
		return (n);
	return (ft_first_digit(n / 10));
}

double	ft_last_digit(double n)
{
	size_t		digit;
	int			first;

	if (n < 10)
		return (n);
	digit = ft_count_digit_d(n);
	first = (int)ft_first_digit(n);
	n = n - first * ft_power_d(10, digit - 1);
	return (ft_last_digit(n));
}
