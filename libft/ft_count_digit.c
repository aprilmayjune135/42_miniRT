/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_digit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/10 17:49:47 by xchen         #+#    #+#                 */
/*   Updated: 2020/12/16 10:58:53 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_digit_u(unsigned long long int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

size_t	ft_count_digit(long long int n)
{
	size_t				i;
	unsigned long long	n2;

	i = 0;
	if (n <= 0)
	{
		n2 = n * -1;
		i++;
	}
	else
		n2 = n;
	while (n2 > 0)
	{
		n2 /= 10;
		i++;
	}
	return (i);
}

size_t	ft_count_digit_d(double n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		n *= -1;
	if (n < 1)
		return (1);
	while (n >= 1)
	{
		n /= 10;
		i++;
	}
	return (i);
}

double	ft_power_d(double base, int power)
{
	int			i;
	double		output;

	i = 0;
	output = 1;
	if (power == 0)
		return (1);
	while (i < power)
	{
		output *= base;
		i++;
	}
	return (output);
}
