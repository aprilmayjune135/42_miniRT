/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 14:07:45 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:28:25 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_countstr(char *str, char c)
{
	size_t	i;
	size_t	nbr;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] == c && str[i])
		i++;
	if (i == len)
		return (0);
	nbr = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && i != len - 1)
			nbr++;
		i++;
	}
	return (nbr + 1);
}

static	void	*ft_freearray(char **array, size_t n)
{
	while (n > 0)
	{
		n--;
		array[n] = NULL;
		free(array[n]);
	}
	free(array);
	return (NULL);
}

static	char	*ft_splitfirst(char *str, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*p;

	i = 0;
	while (str[i] == c)
		i++;
	start = i;
	while (str[i] != c && str[i])
		i++;
	end = i;
	p = ft_substr(str, start, end - start);
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	*p;
	char	**array;
	size_t	nbr;
	size_t	i;

	p = (char *)s;
	if (!p)
		return (NULL);
	nbr = ft_countstr(p, c);
	array = (char **)malloc((nbr + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < nbr)
	{
		array[i] = ft_splitfirst(p, c);
		if (!array[i])
			return (ft_freearray(array, i));
		while (*p == c)
			p++;
		p = ft_memchr(p, (int)c, ft_strlen(p));
		i++;
	}
	array[i] = NULL;
	return (array);
}
