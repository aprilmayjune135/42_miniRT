/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:20:48 by xchen         #+#    #+#                 */
/*   Updated: 2020/11/05 21:12:42 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;

	p = dst;
	q = (unsigned char *)src;
	while (n > 0)
	{
		if (*q == (unsigned char)c)
		{
			*p = *q;
			return (p + 1);
		}
		*p = *q;
		p++;
		q++;
		n--;
	}
	return (NULL);
}
