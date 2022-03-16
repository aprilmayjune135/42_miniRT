/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:20:39 by xchen         #+#    #+#                 */
/*   Updated: 2020/11/05 18:26:12 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;

	p = dst;
	q = (unsigned char *)src;
	if (!p && !q)
		return (NULL);
	while (n > 0)
	{
		*p = *q;
		p++;
		q++;
		n--;
	}
	return (dst);
}
