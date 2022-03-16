/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 18:53:51 by xchen         #+#    #+#                 */
/*   Updated: 2020/10/30 13:10:56 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*p;

	p = (char *)s;
	len = ft_strlen(p);
	while (len >= 0)
	{
		if (p[len] == (char)c)
			return (p + len);
		len--;
	}
	return (NULL);
}
