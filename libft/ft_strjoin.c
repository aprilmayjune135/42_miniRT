/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 12:52:58 by xchen         #+#    #+#                 */
/*   Updated: 2020/12/18 06:30:29 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len_1;
	size_t	len_2;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	p = (char *)malloc((len_1 + len_2 + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_memmove(p, s1, len_1);
	ft_memmove(p + len_1, s2, len_2);
	p[len_1 + len_2] = '\0';
	return (p);
}

char	*ft_strjoin_free(char *s1, char *s2, int n)
{
	char	*p;
	size_t	len_1;
	size_t	len_2;

	if (s1 && s2)
	{
		len_1 = ft_strlen(s1);
		len_2 = ft_strlen(s2);
		p = (char *)malloc((len_1 + len_2 + 1) * sizeof(char));
		if (!p)
			return (NULL);
		ft_memmove(p, s1, len_1);
		ft_memmove(p + len_1, s2, len_2);
		p[len_1 + len_2] = '\0';
	}
	else
		p = NULL;
	if (n == 1 || n == 3)
		free(s1);
	if (n == 2 || n == 3)
		free(s2);
	return (p);
}
