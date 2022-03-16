/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dtoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/09 11:30:34 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:26:26 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <float.h>

static char	*ft_fill_zero(int count_zero)
{
	char	*s;

	if (count_zero <= 0)
		return (ft_strdup(""));
	s = (char *)ft_calloc(count_zero + 1, sizeof(char));
	if (!s)
		return (NULL);
	s = ft_memset(s, '0', count_zero);
	return (s);
}

static char	*ft_front(double n, int decimal_count, int neg_sign)
{
	char		*s;
	size_t		len;
	size_t		i;
	int			first;

	decimal_count = 0;
	len = ft_count_digit_d(n) + neg_sign;
	i = neg_sign;
	s = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (neg_sign == 1)
		s[0] = '-';
	while (i < len)
	{
		if (n < ft_power_d(10, len - 1 - i))
			first = 0;
		else
			first = (int)ft_first_digit(n);
		s[i] = first + '0';
		n = n - first * ft_power_d(10, len - 1 - i);
		i++;
	}
	return (s);
}

static void	ft_process_after_dot(int *decimal, int decimal_count,
			int *fill_zero, double *after_dot)
{
	while (*decimal < decimal_count)
	{
		(*decimal)++;
		(*after_dot) *= 10;
		if ((*after_dot) < 0.99999999)
			(*fill_zero)++;
	}
}

static char	*ft_back(double *ptr_n, int decimal_count)
{
	double			after_dot;
	long long int	int_after_dot;
	int				decimal;
	int				fill_zero;

	decimal = 0;
	fill_zero = 0;
	after_dot = ft_last_digit(*ptr_n) - (int)ft_last_digit(*ptr_n);
	if (after_dot == 0)
		return (ft_fill_zero(decimal_count));
	ft_process_after_dot(&decimal, decimal_count, &fill_zero, &after_dot);
	int_after_dot = ft_dtoi(after_dot);
	if (int_after_dot == 0)
		return (ft_fill_zero(fill_zero));
	if (int_after_dot > after_dot)
	{
		*ptr_n += 1 / ft_power_d(10, decimal);
		if (int_after_dot >= ft_power_d(10, decimal))
			return (ft_fill_zero(decimal_count));
		if (after_dot < 0.99999999)
			fill_zero--;
	}
	return (ft_strjoin_free(ft_fill_zero(fill_zero),
			ft_itoa_u((int_after_dot)), 3));
}

char	*ft_dtoa(double n, int decimal_count)
{
	char		*s_front;
	char		*s_back;
	int			neg_sign;

	if (decimal_count < 0)
		return (NULL);
	if (n >= 0)
		neg_sign = 0;
	if (n < 0)
	{
		n *= -1;
		neg_sign = 1;
	}
	s_back = ft_back(&n, decimal_count);
	s_front = ft_front(n, decimal_count, neg_sign);
	if (decimal_count == 0)
		return (s_front);
	return (ft_strjoin_free(ft_strjoin_free(s_front, ".", 1), s_back, 3));
}
