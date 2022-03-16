/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/19 11:12:24 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/16 12:05:06 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mlx.h>
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# define SP 3
# define PL 4
# define TR 5
# define SQ 6
# define CY 7
# define DS 8
# define CO 9
# define CB 10
# define PR 11
# define EYE_TO_SCREEN 1
# define BUMP_FILE "./texture/brick.bmp"
# define BUMP_SCALE 5

typedef struct s_img{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_vec2{
	double		x;
	double		y;
}				t_vec2;

typedef struct s_vec3{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_matrix{
	t_vec3		row1;
	t_vec3		row2;
	t_vec3		row3;
}				t_matrix;

typedef struct s_int2{
	int			x;
	int			y;
}				t_int2;

typedef struct s_screen{
	double		eye_to_screen;
	double		z;
	t_vec3		viewport;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		normal;
	t_vec3		lower_left_corner;
}				t_screen;

typedef struct s_ray{
	t_vec3		origin;
	t_vec3		dir;
}				t_ray;

typedef struct s_effect{
	int			checker;
	int			wave;
	int			rainbow;
	int			bump;
}				t_effect;

typedef struct s_hit_record{
	t_vec3		point;
	t_vec3		normal_out;
	double		t;
	t_vec2		t_scope;
	int			front_face;
	int			obj_shape;
	t_vec3		obj_color;
	t_vec3		obj_phong;
	t_vec2		texture;
}				t_hit_record;

typedef struct s_tr{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	t_vec3		ab;
	t_vec3		ac;
	t_vec3		normal;
}				t_tr;

typedef struct s_uv{
	t_vec3		u;
	t_vec3		v;
}				t_uv;

typedef struct s_store{
	t_tr		tr[4];
	t_uv		uv;
	t_vec2		checker;
	t_matrix	w_to_l;
	t_matrix	l_to_w;
}				t_store;

typedef struct s_obj{
	int				shape;
	int				index;
	t_vec3			phong;
	t_vec3			color;
	t_effect		effect;
	t_vec3			normal;
	t_vec3			center;
	double			radius;
	t_vec3			color_2;
	t_vec3			size_3d;
	t_store			storage;
	struct s_obj	*next;
}				t_obj;

typedef struct s_scene{
	t_int2		image_size;
	t_vec3		ambient_light;
	int			color_filter;
	t_obj		*cameras;
	t_obj		*lights;
	t_obj		*objs;
	t_vec3		back_color;
	t_vec3		*bump;
}				t_scene;

typedef struct s_minirt{
	void		*mlx;
	void		*win;
	t_img		img;
	t_obj		camera;
	t_screen	screen;
	t_scene		*scene;
	int			save_bmp;
}				t_minirt;

/* parse -> parse_file / effect / bump */

int				check_argument(int fd, int argc, char **argv, int *save_bmp);
int				parse_file(int fd, t_scene **scene);
int				read_effect(char *s, int *pos, t_effect *effect);
int				scene_is_bump(t_obj *obj);
int				parse_bump(t_obj *objs, t_vec3 **bump_data);

/* parse -> parse_nbr */

int				read_int(char *s, int *pos, int *nbr);
int				read_double(char *s, int *pos, double *nbr);
int				read_color(char *s, int *pos, t_vec3 *color);
int				read_vec3(char *s, int *pos, t_vec3 *v);

/* parse -> process_obj */

t_tr			create_tr(t_vec3 p1, t_vec3 p2, t_vec3 p3);
void			process_sq(t_obj *obj);
void			process_pr(t_obj *obj);
void			process_ck(t_obj *obj);
void			process_cb(t_obj *obj);

/* parse -> parse_line */

int				parse_line(char *s, t_scene *scene);
int				check_normal_input(t_vec3 normal);
int				parse_resolut(char *s, t_int2 *image_size);
int				parse_ambient(char *s, t_vec3 *color);
int				parse_filter(char *s, int *color_filter);

/* parse -> parse_obj */

void			process_obj(t_obj *obj);
int				parse_obj(char *s, t_obj **objs, int shape);
int				parse_camera(char *s, t_obj *obj);
int				parse_spot_light(char *s, t_obj *obj);
int				parse_dir_light(char *s, t_obj *obj);
int				parse_sp(char *s, t_obj *obj);
int				parse_pl(char *s, t_obj *obj);
int				parse_tr(char *s, t_obj *obj);
int				parse_sq(char *s, t_obj *obj);
int				parse_cy(char *s, t_obj *obj);
int				parse_ds(char *s, t_obj *obj);
int				parse_cb(char *s, t_obj *obj);

/* parse ->function_array */

int				get_obj_shape(char *s);
int				ft_parse_obj(char *s, t_obj *new, int shape);
int				ft_intersect(t_obj obj, t_ray ray_light, \
					 t_vec2 t_scope, double *t);
int				ft_hit(t_obj obj, t_ray ray, t_hit_record *hit);

/* utils -> minilibx_support */

int				create_color(int t, t_vec3 color);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				close_window(t_minirt *minirt);
int				key_hook_minirt(int keycode, t_minirt *minirt);
int				mouse_hook_minirt(int button, int x, int y, t_minirt *minirt);
void			switch_camera(t_obj *current, t_obj *cameras);
void			rotate_camera(t_obj *camera, int keycode, double delta, \
		t_screen screen);
void			translate_camera(t_obj *camera, int keycode, double delta, \
		t_screen screen);
void			rotate_camera_mouse(t_obj *camera, t_int2 mouse, \
		t_int2	image_size, t_screen screen);

/* utils -> exit */

int				return_error(int result, char *message);
int				exit_program(t_minirt *minirt);
void			free_objs(t_obj **list);
int				exit_parse_error(t_scene **scene);

/*  utils */

int				get_next_line(int fd, char **line);
double			convert_rad(int angle);
double			convert_angle(double rad);
int				obj_list_len(t_obj *list);
t_vec3			reflection_dir(t_vec3 ray_dir, t_vec3 hit_normal);

/* image */

int				create_bmp(t_int2 image_size, t_img image);
void			export_bmp(t_minirt *minirt);
void			init_screen(t_screen *screen, t_obj camera, t_int2 image_size);
void			draw_img(t_img *img, t_scene scene, t_obj camera, \
		t_screen screen);
void			create_img(t_minirt *minirt);
void			display_img(t_minirt *minirt);
void			show_on(char *name, t_minirt *minirt);

/* intersection */
void			process_hit( t_hit_record *hit, t_ray ray, \
					t_vec3 obj_normal, double t);
int				sp_intersect(t_obj sp, t_ray ray, t_vec2 scope, double *t);
int				sp_hit(t_obj sp, t_ray ray, t_hit_record *hit);
int				pl_intersect(t_obj pl, t_ray ray, t_vec2 scope, double *t);
int				pl_hit(t_obj pl, t_ray ray, t_hit_record *hit);
int				ds_intersect(t_obj ds, t_ray ray, t_vec2 scope, double *t);
int				ds_hit(t_obj ds, t_ray ray, t_hit_record *hit);
int				tr_intersect_check(t_tr tr, t_ray ray, t_vec2 scope, double *t);
int				tr_intersect(t_obj tr, t_ray ray, t_vec2 scope, double *t);
int				tr_hit(t_obj tr, t_ray ray, t_hit_record *hit);
int				sq_intersect(t_obj sq, t_ray ray, t_vec2 scope, double *t);
int				sq_hit(t_obj sq, t_ray ray, t_hit_record *hit);
int				cyco_intersect_body(t_obj cy, t_ray ray, \
					t_vec2 scope, double *t_body);
int				cyco_intersect(t_obj cy, t_ray ray, t_vec2 scope, double *t);
int				cyco_hit(t_obj co, t_ray ray, t_hit_record *hit);
int				cb_intersect(t_obj cb, t_ray ray, t_vec2 scope, double *t);
int				cb_hit(t_obj cb, t_ray ray, t_hit_record *hit);
int				pr_intersect(t_obj pr, t_ray ray, t_vec2 scope, double *t);
int				pr_hit(t_obj pr, t_ray ray, t_hit_record *hit);

/* tracing */
t_vec3			apply_checker(t_obj obj, t_hit_record hit);
t_vec3			apply_wave(t_vec3 phit, t_vec3 nhit);
t_vec3			apply_rainbow(t_vec3 center, t_vec3 phit);
t_vec3			bump_normal(t_obj obj, t_hit_record hit, t_vec3 *bump_map);
t_vec3			*bmp_read_pix(int fd);
t_vec3			bmp_read_rgb(unsigned char *s);
t_vec3			perturb_normal(t_vec3 nhit, t_vec3 nmap);
double			get_transmission(t_vec3 light_dir, t_hit_record hit, \
					t_obj *objs);
t_vec3			surface_color(t_scene scene, t_hit_record hit, t_vec3 ray_dir);
t_vec3			ray_trace(t_scene scene, t_ray ray);

/* vector */

t_vec3			create_vec3(double x, double y, double z);
t_vec3			v_multiply_t(double t, t_vec3 orig);
t_vec3			v_add(t_vec3 v1, t_vec3 v2);
t_vec3			v_minus(t_vec3 v1, t_vec3 v2);
t_vec3			v_multiply(t_vec3 v1, t_vec3 v2);
t_vec3			v_divide(t_vec3	v1, t_vec3 v2);
double			v_dot(t_vec3 v1, t_vec3 v2);
t_vec3			v_cross(t_vec3 v1, t_vec3 v2);
double			v_length_squared(t_vec3 v);
double			v_length(t_vec3 v);
t_vec3			v_unit_vector(t_vec3 v);
t_vec2			create_vec2(double x, double y);
t_vec3			ray_at(t_ray ray, double t);
t_vec3			pl_arbitrary_p(t_vec3 normal);

/* vector -> matrix */

t_matrix		create_matrix(t_vec3 v1, t_vec3 v2, t_vec3 v3);
t_matrix		m_multiply_t(double t, t_matrix m);
t_matrix		m_add(t_matrix m1, t_matrix m2);
t_matrix		m_scaler(double a, double b, double c);
t_matrix		create_rot_matrix(int axis, double angle);
t_matrix		m_rotation(t_vec3 old, t_vec3 new);
t_vec3			v_rotation(t_matrix m, t_vec3 v_old);
t_ray			rotate_ray(t_ray ray, t_matrix	w_to_l, t_vec3 obj_center);

#endif
