/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 08:57:14 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:25:03 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *str)
{
	char	*p;
	int		i;
	int		j;
	int		sign;

	p = (char *)str;
	i = 0;
	j = 0;
	sign = 1;
	while (ft_isspace(p[i]) == 1)
		i++;
	if (p[i] == '+')
		i++;
	else if (p[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (p[i] == '0')
		i++;
	while (p[i + j] >= '0' && p[i + j] <= '9')
		j++;
	if (j == 0)
		return (0);
	return (ft_str2int((p + i), j, sign));
}
