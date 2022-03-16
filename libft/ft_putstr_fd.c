/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 10:29:03 by xchen         #+#    #+#                 */
/*   Updated: 2021/02/23 12:37:04 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s)
{
	if (!s)
		write(1, "(null)", 6);
	else
		write(1, s, ft_strlen(s));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		write(fd, "(null)", 6);
	else
		write(fd, s, ft_strlen(s));
}
