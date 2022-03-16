/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 10:31:16 by xchen         #+#    #+#                 */
/*   Updated: 2020/12/18 07:12:51 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if (start + 1 > ft_strlen(s) || !len)
		return (ft_strdup(""));
	p = (char *)ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	return (p);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		p = NULL;
	else if (start + 1 > ft_strlen(s) || !len)
		p = ft_strdup("");
	else
	{
		p = (char *)ft_calloc(len + 1, sizeof(char));
		if (p)
		{
			i = 0;
			while (i < len && s[start + i])
			{
				p[i] = s[start + i];
				i++;
			}
		}
	}
	free(s);
	return (p);
}
