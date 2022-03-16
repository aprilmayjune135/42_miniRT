/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ischar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 20:52:53 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:27:12 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}
