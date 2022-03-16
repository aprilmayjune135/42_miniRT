/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 22:13:02 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:27:33 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long int n)
{
	size_t					size;
	unsigned long long int	n2;
	char					*str;

	size = ft_count_digit(n);
	str = (char *)ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (NULL);
	n2 = n;
	if (n < 0)
	{
		n2 = n * (-1);
		str[0] = '-';
	}
	if (n == 0)
		str[0] = '0';
	while (n2 > 0)
	{
		size--;
		str[size] = n2 % 10 + '0';
		n2 /= 10;
	}
	return (str);
}

char	*ft_itoa_u(unsigned long long int n)
{
	unsigned int			size;
	char					*str;

	size = ft_count_digit_u(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		size--;
		str[size] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
