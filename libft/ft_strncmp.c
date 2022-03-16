/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 20:33:29 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:29:01 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	if (!n)
		return (0);
	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	i = 0;
	while (p[i] == q[i] && i < n - 1 && p[i] && q[i])
		i++;
	return (p[i] - q[i]);
}
