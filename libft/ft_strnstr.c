/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 19:52:15 by xchen         #+#    #+#                 */
/*   Updated: 2020/11/09 11:38:05 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*p;
	char	*q;
	size_t	i;
	size_t	j;

	p = (char *)haystack;
	q = (char *)needle;
	i = 0;
	if (!ft_strlen(q))
		return (p);
	while (p[i] && i < len)
	{
		j = 0;
		while (p[i] != q[j] && p[i] && i < len)
			i++;
		while (p[i] == q[j] && p[i] && q[j] && i < len)
		{
			i++;
			j++;
		}
		if (q[j] == '\0')
			return (p + i - j);
	}
	return (NULL);
}
