/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   other_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 17:21:03 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 15:17:09 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "other_check.h"

void	print_mark(char c)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		printf("%c", c);
		i++;
	}
	printf("\n");
}

void	print_vector(t_vec3 v, int digit)
{
	printf("x(%.*f)-y(%.*f)-z(%.*f)\n", digit, v.x, digit, v.y, digit, v.z);
}

void	print_matrix(t_matrix m, int digit)
{
	print_vector(m.row1, digit);
	print_vector(m.row2, digit);
	print_vector(m.row3, digit);
}

void	print_camera(t_obj camera, int digit)
{
	printf("Camera # %d\n", camera.index);
	print_vector(camera.center, digit);
	print_vector(camera.normal, digit);
	printf("%.*f\n", digit, camera.radius);
}

void	print_camera_list(t_obj *camera, int digit)
{
	t_obj		*temp;
	int			i;

	temp = camera;
	i = 0;
	if (!camera)
		printf("Empty list!\n");
	while (temp)
	{
		printf("[%d]", i++);
		print_camera(*temp, digit);
		temp = temp->next;
	}
	printf("----------------\n");
}

void	print_key_code(int keycode)
{
	printf("You just pressed key: [ %d ]\n", keycode);
}

void	print_bmp_header(int fd)
{
	unsigned char	s1[54];
	int				output;
	int				i;

	output = read(fd, s1, 54);
	if (output == -1)
	{
		printf("Error in get next line!'n");
		close(fd);
		return ;
	}
	printf("*********File Header*********\n%x %x\n%x %x %x %x\n%x %x\n%x %x\n%x %x %x %x\n", (int)s1[0], (int)s1[1], (unsigned int)s1[2], (int)s1[3], (int)s1[4], (int)s1[5], (int)s1[6], (int)s1[7], (int)s1[8], (int)s1[9], (int)s1[10], (int)s1[11], (int)s1[12], (int)s1[13]);
	printf("*********Info Header*********\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x\n%x %x\n", (int)s1[14], (int)s1[15], (int)s1[16], (int)s1[17], (int)s1[18], (int)s1[19], (int)s1[20], (int)s1[21], (int)s1[22], (int)s1[23], (int)s1[24], (int)s1[25], (int)s1[26], (int)s1[27], (int)s1[28], (int)s1[29]);
	i = 30;
	while (i < 54)
	{
		printf("%x", (int)s1[i]);
		i++;
	}
	read(fd, s1, 8);
	printf("\n*********Pixel Data*********\n");
	print_vector(bmp_read_rgb(s1), 0);
	print_vector(bmp_read_rgb(s1 + 4), 0);
	i = 0;
	while (i < 8)
	{
		printf("%x", (int)s1[i]);
		i++;
	}
	close (fd);
}
