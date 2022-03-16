/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_otoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 22:13:02 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:28:01 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	ft_nbrdigit(unsigned long long int n)
{
	unsigned int	i;

	i = 0;
	while (n > 0)
	{
		n /= 8;
		i++;
	}
	return (i);
}

char	*ft_otoa(unsigned long long int n)
{
	unsigned int	size;
	char			*str;

	size = ft_nbrdigit(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		size--;
		str[size] = n % 8 + '0';
		n /= 8;
	}
	return (str);
}
