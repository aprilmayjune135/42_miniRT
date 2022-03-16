/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 18:53:51 by xchen         #+#    #+#                 */
/*   Updated: 2020/10/30 13:05:26 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	p = (char *)s;
	if (*p == (char)c)
		return (p);
	i = 1;
	while (p[i - 1])
	{
		if (p[i] == (char)c)
			return (p + i);
		i++;
	}
	return (NULL);
}
