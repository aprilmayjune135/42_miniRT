/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:50:34 by xchen         #+#    #+#                 */
/*   Updated: 2020/12/18 06:35:35 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;

	len = ft_strlen((char *)s1);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_memmove(p, s1, len);
	*(p + len) = '\0';
	return (p);
}

char	*ft_strdup_free(char *dst, char *src, int n)
{
	size_t	len;
	char	*p;

	if (src)
	{
		len = ft_strlen((char *)src);
		p = (char *)malloc((len + 1) * sizeof(char));
		if (!p)
			return (NULL);
		ft_memmove(p, src, len);
		*(p + len) = '\0';
	}
	else
		p = NULL;
	if (n == 1 || n == 3)
		free(dst);
	if (n == 2 || n == 3)
		free(src);
	return (p);
}
