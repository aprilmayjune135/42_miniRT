/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 09:36:20 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 19:14:26 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bmp_fill_number(unsigned char *s, unsigned int nbr)
{
	s[0] = (unsigned char)(nbr);
	s[1] = (unsigned char)(nbr >> 8);
	s[2] = (unsigned char)(nbr >> 16);
	s[3] = (unsigned char)(nbr >> 24);
}

void	bmp_file_header(t_int2 image_size, int fd, int line_len)
{
	unsigned char	s[14];
	unsigned int	file_size;

	file_size = 54 + line_len * image_size.y;
	ft_memset(s, 0, 14);
	ft_memcpy(s, "BM", 2);
	bmp_fill_number(s + 2, file_size);
	s[10] = 54;
	write(fd, s, 14);
}

void	bmp_info_header(t_int2 image_size, int fd, int bpp)
{
	unsigned char	s[40];

	ft_memset(s, 0, 40);
	s[0] = 40;
	bmp_fill_number(s + 4, image_size.x);
	bmp_fill_number(s + 8, image_size.y);
	s[12] = 1;
	s[14] = bpp;
	write(fd, s, 40);
}

int	create_bmp(t_int2 image_size, t_img image)
{
	int				bmp;
	int				pad;
	int				i;
	int				line_len;
	unsigned char	padding[3];

	bmp = open("./image.bmp", O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	if (bmp == -1)
		return (return_error(-1, "Creating bmp file failed!\n"));
	line_len = image_size.x * (image.bits_per_pixel / 8);
	pad = (4 - line_len % 4) % 4;
	ft_memset(padding, 0, 3);
	bmp_file_header(image_size, bmp, line_len + pad);
	bmp_info_header(image_size, bmp, image.bits_per_pixel);
	i = image_size.y - 1;
	while (i >= 0)
	{
		write(bmp, image.addr + (image.line_length * i), line_len);
		if (pad)
			write(bmp, padding, pad);
		i--;
	}
	close(bmp);
	ft_putstr("bmp image saved successfully! :)\n");
	return (1);
}

void	export_bmp(t_minirt *minirt)
{
	create_img(minirt);
	create_bmp(minirt->scene->image_size, minirt->img);
	mlx_destroy_image(minirt->mlx, minirt->img.img);
	exit_program(minirt);
}
