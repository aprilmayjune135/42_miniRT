/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_comparison.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 14:34:34 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:26:02 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

long long int	ft_min(int count, ...)
{
	va_list	v1;
	va_list	v2;
	int		min;
	int		temp;

	va_start(v1, count);
	va_copy(v2, v1);
	min = va_arg(v2, long long int);
	while (count > 1)
	{
		temp = va_arg(v2, long long int);
		if (temp < min)
			min = temp;
		count--;
	}
	va_end(v2);
	va_end(v1);
	return (min);
}

long long int	ft_max(int count, ...)
{
	va_list	v1;
	va_list	v2;
	int		max;
	int		temp;

	va_start(v1, count);
	va_copy(v2, v1);
	max = va_arg(v2, long long int);
	while (count > 1)
	{
		temp = va_arg(v2, long long int);
		if (temp > max)
			max = temp;
		count--;
	}
	va_end(v2);
	va_end(v1);
	return (max);
}

double	ft_min_double(int count, ...)
{
	va_list	v1;
	va_list	v2;
	double	min;
	double	temp;

	va_start(v1, count);
	va_copy(v2, v1);
	min = va_arg(v2, double);
	while (count > 1)
	{
		temp = va_arg(v2, double);
		if (temp < min)
			min = temp;
		count--;
	}
	va_end(v2);
	va_end(v1);
	return (min);
}

double	ft_max_double(int count, ...)
{
	va_list	v1;
	va_list	v2;
	double	max;
	double	temp;

	va_start(v1, count);
	va_copy(v2, v1);
	max = va_arg(v2, double);
	while (count > 1)
	{
		temp = va_arg(v2, double);
		if (temp > max)
			max = temp;
		count--;
	}
	va_end(v2);
	va_end(v1);
	return (max);
}
