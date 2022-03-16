/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_axtoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 08:57:14 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:25:29 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_hexa_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else
		return (ft_tolower(c) - 'a' + 10);
}

static long long int	ft_str2nbr(char *str, int j)
{
	unsigned long long int	power;
	unsigned long long int	output;
	int						len;

	output = 0;
	len = j;
	power = 1;
	while (len > 0)
	{
		output += ft_hexa_int(str[len - 1]) * power;
		power *= 16;
		len--;
	}
	return (output);
}

long long int	ft_axtoi(const char *str)
{
	char	*p;
	int		i;
	int		j;

	p = (char *)str;
	i = 0;
	j = 0;
	while (p[i] == '0')
		i++;
	while ((p[i + j] >= '0' && p[i + j] <= '9')
		|| (ft_tolower(p[i + j]) >= 'a' && ft_tolower(p[i + j]) <= 'f'))
		j++;
	if (j == 0)
		return (0);
	return (ft_str2nbr((p + i), j));
}
