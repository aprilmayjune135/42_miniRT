/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_gtoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 22:16:03 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 20:27:01 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cut_tail_zero(char *s, size_t position)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (position >= ft_strlen(s))
		return (s);
	while (position - i > 0 && s[position - i] == '0')
		i++;
	return (ft_substr(s, 0, position - i + 1));
}

static size_t	ft_pos_chr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_gtoa(double n, int precision, char letter_g)
{
	int		digit;
	size_t	pos_e;
	size_t	len;
	char	letter_e;
	char	*s;

	precision = ft_max(2, 1, precision);
	if (letter_g == 'g')
		letter_e = 'e';
	else
		letter_e = 'E';
	digit = (int)ft_count_digit_d(n);
	if (digit <= precision)
	{
		s = ft_dtoa(n, precision - digit);
		return (ft_cut_tail_zero(s, ft_strlen(s) - 1));
	}
	else
	{
		s = ft_etoa(n, precision - 1, letter_e);
		len = ft_strlen(s);
		pos_e = ft_pos_chr(s, letter_e);
		return (ft_strjoin(ft_cut_tail_zero(s, pos_e - 1),
				ft_substr(s, pos_e, len - pos_e)));
	}
}
