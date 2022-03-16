/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_bump.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/13 19:43:30 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/13 19:48:06 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scene_is_bump(t_obj *objs)
{
	t_obj	*temp;

	temp = objs;
	while (temp)
	{
		if (temp->effect.bump == 1)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_vec3	bmp_read_rgb(unsigned char *s)
{
	t_vec3	normal;

	normal.x = (double)((int)s[2]) / 255 * 2 - 1;
	normal.y = (double)((int)s[1]) / 255 * 2 - 1;
	normal.z = (double)((int)s[0]) / 255 * 2 - 1;
	return (v_unit_vector(normal));
}

t_vec3	*bmp_read_pix(int fd)
{
	unsigned char	s[3072];
	unsigned char	temp[0x8a];
	t_vec3			*bump_map;
	t_int2			pix;

	bump_map = (t_vec3 *)malloc(256 * 256 * sizeof(t_vec3));
	if (bump_map)
	{
		read(fd, temp, 0x8a);
		pix.y = 256;
		while (pix.y > 0)
		{
			pix.y--;
			pix.x = 0;
			read(fd, s, 3072);
			while (pix.x < 256)
			{
				*(bump_map + (pix.y * 256 + pix.x))
					= bmp_read_rgb(s + pix.x * 3);
				pix.x++;
			}
		}
	}
	close(fd);
	return (bump_map);
}

int	parse_bump(t_obj *objs, t_vec3 **bump_data)
{
	int	fd;

	if (!scene_is_bump(objs))
		return (0);
	fd = open(BUMP_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	*bump_data = bmp_read_pix(fd);
	if (!*bump_data)
		return (-1);
	return (1);
}
