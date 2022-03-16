/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 13:53:50 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:29:11 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_findchar(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*p;
	char	*q;

	p = (char *)s1;
	q = (char *)set;
	if (!p)
		return (NULL);
	j = ft_strlen(p);
	if (j == 0)
		return (ft_strdup(""));
	i = 0;
	j--;
	while (p[i] && ft_findchar(q, p[i]))
		i++;
	while (j > 0 && ft_findchar(q, p[j]))
		j--;
	if (j < i)
		return (ft_strdup(""));
	return (ft_substr(p, i, j - i + 1));
}
