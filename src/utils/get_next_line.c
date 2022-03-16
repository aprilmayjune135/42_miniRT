/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 16:26:03 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 17:52:43 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define BUFFER_SIZE 200

size_t	gnl_cpylen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_add_line(char *dst, char *src)
{
	size_t	i;
	size_t	j;
	char	*temp;

	temp = (char *)malloc((gnl_strlen(dst) + gnl_cpylen(src) + 1)
			* sizeof(char));
	if (temp)
	{
		i = 0;
		while (dst && dst[i])
		{
			temp[i] = dst[i];
			i++;
		}
		j = 0;
		while (src[j] && src[j] != '\n')
		{
			temp[i + j] = src[j];
			j++;
		}
		temp[i + j] = '\0';
	}
	free(dst);
	return (temp);
}

void	ft_reduce_line(char *dst, char *src)
{
	size_t	i;
	size_t	start;
	size_t	n;

	i = 0;
	start = gnl_cpylen(src) + 1;
	n = BUFFER_SIZE + 1;
	if (start >= n)
	{
		ft_bzero(dst, n);
		return ;
	}
	while (src[start + i] && start + i < n)
	{
		dst[i] = src[start + i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
}

int	get_next_line(int fd, char **line)
{
	int				result;
	char			buf[BUFFER_SIZE + 1];
	static char		str_rest[BUFFER_SIZE + 1];

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || !line || fd < 0)
		return (-1);
	*line = ft_add_line(NULL, str_rest);
	if (!*line)
		return (-1);
	result = gnl_strlen(str_rest) - gnl_cpylen(str_rest);
	ft_reduce_line(str_rest, str_rest);
	if (result > 0)
		return (1);
	while (!result || !buf[gnl_cpylen(buf)])
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		result = read(fd, buf, BUFFER_SIZE);
		if (result < 1)
			return (result);
		*line = ft_add_line(*line, buf);
		if (!*line)
			return (-1);
	}
	ft_reduce_line(str_rest, buf);
	return (1);
}
