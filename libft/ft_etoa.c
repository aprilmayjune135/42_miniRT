/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_etoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/09 11:06:08 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:26:54 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_etoa_big(double n, int precision, char letter_e)
{
	double	front;
	int		digit;
	char	*s_middle;

	digit = ft_count_digit_d(n);
	front = n / ft_power_d(10, digit - 1);
	s_middle = (char *)ft_calloc(3, sizeof(char));
	if (!s_middle)
		return (NULL);
	s_middle[0] = letter_e;
	s_middle[1] = '+';
	if (digit - 1 < 10)
		return (ft_strjoin(ft_strjoin(ft_dtoa(front, precision), s_middle),
				ft_strjoin("0", ft_itoa(digit - 1))));
	else
		return (ft_strjoin(ft_strjoin(ft_dtoa(front, precision), s_middle),
				ft_itoa(digit - 1)));
}

size_t	ft_count_decimal_d(double n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n < 1)
	{
		n *= 10;
		i++;
	}
	return (i);
}

static char	*ft_etoa_small(double n, int precision, char letter_e)
{
	double	front;
	int		decimal;
	char	*s_middle;

	decimal = ft_count_decimal_d(n);
	front = n * ft_power_d(10, decimal);
	s_middle = (char *)ft_calloc(3, sizeof(char));
	if (!s_middle)
		return (NULL);
	s_middle[0] = letter_e;
	s_middle[1] = '-';
	if (decimal < 10)
		return (ft_strjoin(ft_strjoin(ft_dtoa(front, precision), s_middle),
				ft_strjoin("0", ft_itoa(decimal))));
	else
		return (ft_strjoin(ft_strjoin(ft_dtoa(front, precision), s_middle),
				ft_itoa(decimal)));
}

char	*ft_etoa(double n, int precision, char letter_e)
{
	if (n >= 1 || n <= -1)
		return (ft_etoa_big(n, precision, letter_e));
	else
		return (ft_etoa_small(n, precision, letter_e));
}
