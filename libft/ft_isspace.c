/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 20:54:52 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:27:23 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}
