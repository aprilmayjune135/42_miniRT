/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:20:58 by xchen         #+#    #+#                 */
/*   Updated: 2020/11/05 19:08:37 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	p = dst;
	q = (unsigned char *)src;
	if (!p && !q)
		return (NULL);
	if (src < dst && dst < src + len)
	{
		i = len;
		while (i > 0)
		{
			*(p + i - 1) = *(q + i - 1);
			i--;
		}
		return (p);
	}
	i = 0;
	while (i < len)
	{
		*(p + i) = *(q + i);
		i++;
	}
	return (p);
}
