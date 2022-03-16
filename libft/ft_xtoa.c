/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_xtoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 22:13:02 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:30:40 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	ft_nbrdigit(unsigned long long int n)
{
	unsigned int	i;

	i = 0;
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static	char	ft_hexadecimal_letter(int n)
{
	if (n < 10)
		return (n + '0');
	return ((n - 10) + 'a');
}

char	*ft_xtoa(unsigned long long int n)
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
		str[size] = ft_hexadecimal_letter(n % 16);
		n /= 16;
	}
	return (str);
}

char	*ft_xtoa_negative(long long int n)
{
	unsigned int			size;
	unsigned int			i;
	char					*str;
	unsigned long long int	n2;

	n2 = (n * -1) - 1;
	size = ft_nbrdigit(n2);
	i = 8;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (n2 > 0)
	{
		size--;
		i--;
		str[i] = ft_hexadecimal_letter(15 - (n2 % 16));
		n2 /= 16;
	}
	while (i > 0)
	{
		i--;
		str[i] = 'f';
	}
	return (str);
}
