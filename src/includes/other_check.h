#ifndef OTHER_CHECK_H
# define OTHER_CHECK_H
# include <stdio.h>
# include <string.h>
# include "minirt.h"

void			print_mark(char c);
void			print_vector(t_vec3 v, int digit);
void			print_matrix(t_matrix m, int digit);
void			print_camera(t_obj camera, int digit);
void			print_camera_list(t_obj *camera, int digit);
void			print_key_code(int keycode);
void			print_bmp_header(int fd);

#endif